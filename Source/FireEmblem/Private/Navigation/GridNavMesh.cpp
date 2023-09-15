// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/GridNavMesh.h"

#pragma optimize("", off)

// Sets default values
AGridNavMesh::AGridNavMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGridNavMesh::Scan()
{
	/* ALGO:
	* Create nodes
	* place them where needed
	* mark them as walkable or not
	* defines connections
	* defines default cost
	*/

	if (!PerformSanityCheck())
	{
		// add another error message?
		// probably too much, as we most likely won't call this from outside of the scanning method

		return;
	}

	SetupGrid();

	CreateTiles();

	CalculateTilesPositions();

	CalculateTilesConnections();

	DrawTiles();
}

void AGridNavMesh::DrawTiles() const
{
	// might move it to a rendering component
	for (const auto& tile : Tiles)
	{
		DrawDebugBox(GetWorld(), tile.WorldPosition, TileSize, tile.WalkableMask > 0 ? FColor::Blue : FColor::Red, true);

		for (int i = 0; i < 4; ++i)
		{
			FGridTile neighbour;
			if (GetNeighbourAlongDirection(tile, i, neighbour))
				DrawDebugLine(GetWorld(), tile.WorldPosition, neighbour.WorldPosition, FColor::Red, true);
		}
	}
}

void AGridNavMesh::BeginPlay()
{
	Super::BeginPlay();

	Scan();
}

void AGridNavMesh::SetupGrid()
{
	ClearTiles();

	BottomLeftPosition = GetActorLocation() - (FVector(TileCount / 2) * TileSize);

	NeighbourOffset.Add(TileCount.X); // up
	NeighbourOffset.Add(1); // right
	NeighbourOffset.Add(-TileCount.X); // down
	NeighbourOffset.Add(-1); // left

	NeighbourXOffsets.Add(1); // up
	NeighbourXOffsets.Add(0); // right dir
	NeighbourXOffsets.Add(-1); // down dir
	NeighbourXOffsets.Add(0); // left
	
	NeighbourYOffsets.Add(0); // up
	NeighbourYOffsets.Add(1); // right
	NeighbourYOffsets.Add(0); // down
	NeighbourYOffsets.Add(-1); // left
}

void AGridNavMesh::CreateTiles()
{
	for (int i = 0; i < TileCount.X; ++i)
	{
		for (int j = 0; j < TileCount.Y; ++j)
		{
			int index = i * TileCount.Y + j;
			FGridTile& tile = Tiles[index];
			tile.GridIndex = index;
		}
	}
}

void AGridNavMesh::ClearTiles(bool bShouldReinit /*= true*/)
{
	Tiles.Empty();

	if (bShouldReinit)
		Tiles.Init(FGridTile(), TileCount.X * TileCount.Y);

	FlushPersistentDebugLines(GetWorld());
}

void AGridNavMesh::CalculateTilesPositions()
{
	for (int i = 0; i < TileCount.X; ++i)
	{
		for (int j = 0; j < TileCount.Y; ++j)
		{
			CalculateTile(i, j);
		}
	}
}

void AGridNavMesh::CalculateTile(int aXIndex, int aYIndex)
{
	int index = aXIndex * TileCount.Y + aYIndex;
	FGridTile& tile = Tiles[index];

	// default world position for this tile, before doing raycast test
	tile.WorldPosition = FVector(aXIndex * TileSize.X, aYIndex * TileSize.Y, TileSize.Z) + BottomLeftPosition;

	FVector start = FVector(tile.WorldPosition.X, tile.WorldPosition.Y, tile.WorldPosition.Z + TraceLength);
	FVector end = FVector(tile.WorldPosition.X, tile.WorldPosition.Y, tile.WorldPosition.Z - TraceLength);

	TArray<FHitResult> results;
	bool hit = GetWorld()->SweepMultiByChannel(results, start, end, GetActorRotation().Quaternion(), ECC_GridMeshWalkable, FCollisionShape::MakeSphere(AgentRadius));

	if (hit)
	{
		// as we only support one layer for the grid, we will take the first result for our position
		// later, we are planning in supporting multi layer grids

		FHitResult res = results[0];
		tile.WorldPosition.Z = res.Location.Z;

		// ensure that the tile is walkable depending on the agent max slope
		float angle = FVector::DotProduct(res.ImpactNormal, GetActorUpVector());
		float slope = FMath::Cos(FMath::DegreesToRadians(AgentMaxSlope));

		tile.WalkableMask = angle >= slope;
	}
}

void AGridNavMesh::CalculateTilesConnections()
{
	for (int i = 0; i < TileCount.X; ++i)
	{
		for (int j = 0; j < TileCount.Y; ++j)
		{
			CalculateTileConnections(i, j);
		}
	}
}

void AGridNavMesh::CalculateTileConnections(int aXIndex, int aYIndex)
{
	int index = aXIndex * TileCount.Y + aYIndex;
	FGridTile& tile = Tiles[index];

	// reset neighbours in case the tile isn't walkable
	if (tile.WalkableMask == 0)
	{
		tile.NeighbourMask = 0;
		return;
	}

	// as we only support four directions currently (up, down, left, right) only test for those
	// later on, we might support diagonals (and hexes?)
	for (int i = 0; i < 4; ++i)
	{
		int x = aXIndex + NeighbourXOffsets[i];
		int y = aYIndex + NeighbourYOffsets[i];

		// Check if the new position is inside the grid
		if (x >= 0 && y >= 0 && x < TileCount.X && y < TileCount.Y) 
		{
			FGridTile& neighbour = Tiles[index + NeighbourOffset[i]];

			if (IsConnectionValid(tile, neighbour))
			{
				// Enable connection i
				tile.NeighbourMask |= 1 << i;
			}
		}
	}
}

bool AGridNavMesh::PerformSanityCheck()
{
	// this should perform a bunch of test to ensure everything is setup correctly
	// if not, give a message to the user

	if (GenerationMethod == EFEGridGenerationMethod::BOUNDS && !GridBounds)
	{
		// add log

		return false;
	}

	return true;
}

bool AGridNavMesh::IsConnectionValid(const FGridTile& aTile, const FGridTile& aPossibleNeighbour) const
{
	// if any of the tiles isn't walkable, no connection can be done
	if (aTile.WalkableMask == 0 || aPossibleNeighbour.WalkableMask == 0)
		return false;

	// shall we add other tests here?

	return true;
}

bool AGridNavMesh::GetNeighbourAlongDirection(const FGridTile& aTile, int aDirection, FGridTile& outNeighbour) const
{
	if (!aTile.HasConnectionAlongDirection(aDirection))
		return false;

	outNeighbour = Tiles[aTile.GridIndex + NeighbourOffset[aDirection]];

	return true;
}

#pragma optimize("", on)