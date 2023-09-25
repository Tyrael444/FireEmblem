// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/SubGrid.h"

#include "Components/BoxComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Navigation/Components/GridAnchorComponent.h"
#include "Navigation/GridManager.h"

// Sets default values
ASubGrid::ASubGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GridAnchor = CreateDefaultSubobject<UGridAnchorComponent>("Grid Anchor");
	GridAnchor->SetupAttachment(RootComponent);

	HeightmapBounds = CreateDefaultSubobject<UBoxComponent>("Heightmap Bounds");
	HeightmapBounds->SetupAttachment(GridAnchor);
	HeightmapBounds->SetVisibility(ShowBounds);
}

#pragma region Accessors

const FIntPoint& ASubGrid::GetGridSize() const
{
	return GridSize;
}

const int& ASubGrid::GetRelativeGridIndex() const
{
	return RelativeGridIndex;
}

#pragma endregion

#pragma region Super Overrides

void ASubGrid::OnConstruction(const FTransform& Transform)
{
	FVector newLocation = AGridManager::GetInstance()->FindClosestTileToSnapTo(GetActorLocation());
	newLocation.Z = AGridManager::GetInstance()->GetActorLocation().Z;
	GridAnchor->SetWorldLocation(newLocation);

	RelativeGridIndex = AGridManager::GetInstance()->ConvertLocationToIndex3DNaive(GetActorLocation());		
	
	HeightmapBounds->SetVisibility(ShowBounds);
	if (ShowBounds)
		AdjustHeighmapBounds();

	if (ShouldSpawnGridMeshes)
	{
		DefaultTile->SetStaticMesh((TileMeshOverride) ? TileMeshOverride : AGridManager::GetInstance()->GetDefaultTileMesh());

		DefaultTile->SetHiddenInGame(false);
	}
	else
		DefaultTile->SetVisibility(true);
}

#pragma endregion

#pragma region Subgrid Generation

void ASubGrid::AdjustHeighmapBounds()
{
	FVector location;
	FVector scale;
	AGridManager::GetInstance()->ScaleCollisionAndHeightmapBoxes(true, GridSize, location, scale);

	if (AGridManager::GetInstance()->GetHeighType() == EGridHeight::NONE)
	{
		location.Z = 0;
		scale.Z = 0;
	}
	else
	{
		location.Z = (AGridManager::GetInstance()->GetMinHeight() + AGridManager::GetInstance()->GetMaxHeight()) / 2;
		scale.Z = (AGridManager::GetInstance()->GetMaxHeight() - AGridManager::GetInstance()->GetMinHeight()) / AGridManager::GetInstance()->GetDefaultTileWidth();
	}

	HeightmapBounds->SetRelativeTransform(FTransform(FRotator(), location, scale));
}

void ASubGrid::SpawnGridMeshes()
{
	FVector defaultTileLocation = GridAnchor->GetRelativeLocation();
	if (AGridManager::GetInstance()->GetHeighType() != EGridHeight::NONE)
		defaultTileLocation.Z = 0.f;

	FVector scale(1, 1, 1);

	for (int i = 0; i < (GridSize.X * GridSize.Y); ++i)
	{
		FVector location = AGridManager::GetInstance()->GetDisplayTileLocationFromIndex(i, GridSize);
		DefaultTile->AddInstance(FTransform(FRotator(), location, scale));
	}
}

#pragma endregion