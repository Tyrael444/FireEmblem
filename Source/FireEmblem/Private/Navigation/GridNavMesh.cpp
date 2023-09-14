// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/GridNavMesh.h"

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

	CreateTiles();

	CalculateTilesPositions();

	CalculateTilesConnections();

	DrawTiles();
}

void AGridNavMesh::DrawTiles() const
{
	for (const auto& tile : Tiles)
	{
		DrawDebugBox(GetWorld(), tile.WorldPosition, TileSize, tile.WalkableMask > 0 ? FColor::Blue : FColor::Red);
	}
}

void AGridNavMesh::BeginPlay()
{
	Super::BeginPlay();

	Scan();
}

void AGridNavMesh::CreateTiles()
{
	ClearTiles();

	Tiles.Init(FGridTile(), TileCount.X * TileCount.Y);

	for (int i = 0; i < TileCount.X; ++i)
	{
		for (int j = 0; j < TileCount.Y; ++j)
		{
			int index = i * TileCount.Y + j;
			FGridTile& tile = Tiles[index];
			tile.GridIndex = index;
		}
	}

	BottomLeftPosition = GetActorLocation() - (FVector(TileCount / 2) * TileSize);
}

void AGridNavMesh::ClearTiles()
{
	Tiles.Empty();
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
		tile.WalkableMask = 1;
	}
}

void AGridNavMesh::CalculateTilesConnections()
{
}

void AGridNavMesh::CalculateTileConnections(int aXIndex, int aYIndex)
{
}

bool AGridNavMesh::PerformSanityCheck()
{
	if (GenerationMethod == EFEGridGenerationMethod::BOUNDS && !GridBounds)
	{
		// add log

		return false;
	}

	return true;
}