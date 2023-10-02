// Fill out your copyright notice in the Description page of Project Settings.

#include "Navigation/GridManager.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/Tile/BaseTile.h"

#pragma optimize("", off)

#pragma region Singleton

AGridManager* AGridManager::Instance = nullptr;

AGridManager* AGridManager::GetInstance()
{
	if (!Instance)
	{
		TArray<AActor*> actors;

		UGameplayStatics::GetAllActorsOfClass(GEngine->GameViewport->GetWorld(), AGridManager::StaticClass(), actors);
		if (actors.Num() == 0)
		{
			// add log that none was created

			Instance = NewObject<AGridManager>();
		}
		else
		{
			if (actors.Num() >= 2)
			{
				// add log, maybe destroy others ?
			}

			Instance = Cast<AGridManager>(actors[0]);
		}
	}

	return Instance;
}

AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultTile = CreateDefaultSubobject<UInstancedStaticMeshComponent>("Default Tile");
	DefaultTile->SetupAttachment(RootComponent);

	CollisionPlane = CreateDefaultSubobject<UStaticMeshComponent>("Collision Plane");
	CollisionPlane->SetupAttachment(RootComponent);

	HeightmapBounds = CreateDefaultSubobject<UBoxComponent>("Heightmap Bounds");
	HeightmapBounds->SetupAttachment(RootComponent);
	HeightmapBounds->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	GridDecal = CreateDefaultSubobject<UDecalComponent>("Grid Decal");
	GridDecal->SetupAttachment(RootComponent);
}

AGridManager::~AGridManager()
{
	Instance = nullptr;
}

#pragma endregion

#pragma region Super overrides

void AGridManager::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ValidateData();

	SetupScaleAndDefaultTiles();

	SetupCollisionPlane();

	SetupHeightmapBox();

	SpawnTileGrid();

	ScaleAutoVolumes();

	SetupGridArrays();

	if (DebugDisplayPregeneratedGameplayGrids)
		DebugPregenerateGameplayGrids();
}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
}

void AGridManager::PostEditChangeProperty(FPropertyChangedEvent& anEvent)
{
	Super::PostEditChangeProperty(anEvent);

	/* bunch of test here to ensure that the values we are trying to set make sense */
	FName propertyName = (anEvent.Property != nullptr) ? anEvent.Property->GetFName() : FName("NONE");
	if (propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, Heightmap))
	{
		AutoHeightBasedEdgeCosts = Heightmap == EGridHeight::MULTI_LEVEL;
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, MaxHeight)
		|| propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, HeightBetweenLevels))
	{
		MaxLevels = FMath::TruncToInt(MaxHeight / HeightBetweenLevels);
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, HeightSlowIncrement)
		|| propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, HeightImpassableCutoff))
	{
		if (HeightSlowIncrement > HeightImpassableCutoff)
		{
			HeightSlowIncrement = HeightImpassableCutoff;
		}
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, DebugDisplayPregeneratedGameplayGrids) && !DebugDisplayPregeneratedGameplayGrids)
	{
		DebugDisplayTileIndexes = false;
		DebugDisplayTileEdges = false;
	}
	else if (propertyName == GET_MEMBER_NAME_CHECKED(AGridManager, DebugDisplayTileEdges) && !DebugDisplayTileEdges)
	{
		if (EdgeMeshInstances)
			EdgeMeshInstances->ClearInstances();
	}
}

#pragma endregion

#pragma region Grid Setup

void AGridManager::ValidateData()
{
	/* we simply ensure that our values make sense */
	MaxLevels = FMath::TruncToInt(MaxHeight / HeightBetweenLevels);

	if (HeightSlowIncrement > HeightImpassableCutoff)
	{
		HeightSlowIncrement = HeightImpassableCutoff;
	}

	AutoHeightBasedEdgeCosts = (Heightmap == EGridHeight::MULTI_LEVEL);
}

void AGridManager::SetupScaleAndDefaultTiles()
{
	check(DefaultTile);

	DefaultTile->SetVisibility(ShowDefaultTile, true);
	DefaultTile->SetStaticMesh(DefaultTileMesh);

	CalculateTileSize();
}

bool AGridManager::CalculateTileSize()
{
	/* we might add some error/logging on this kind of case */
	if (!DefaultTileMesh)
		return false;

	/* sets the tile size. we could either only take the X axis bound as we are using squared grids */
	FBoxSphereBounds bounds = DefaultTileMesh->GetBounds();
	TileSize.X = bounds.BoxExtent.X * 2;
	TileSize.Y = bounds.BoxExtent.X * 2;

	return true;
}

void AGridManager::SetupCollisionPlane()
{
	check(CollisionPlane);

	FVector location;
	FVector scale;
	ScaleCollisionAndHeightmapBoxes(false, FIntPoint(), location, scale);

	CollisionPlane->SetRelativeTransform(FTransform(FRotator(), location, FVector(scale.X * 2.f, scale.Y * 2.f, 1.f)));
	CollisionPlane->SetVisibility(ShowCollisionPlane);
}

void AGridManager::ScaleCollisionAndHeightmapBoxes(bool bOverrideSize, const FIntPoint& aSizeOverride, FVector& outLocation, FVector& outScale)
{
	int localX;
	int localY;

	if (bOverrideSize)
	{
		localX = aSizeOverride.X;
		localY = aSizeOverride.Y;
	}
	else
	{
		switch (ShowHeightmapBoundingBox)
		{
		case EGridBoundingBox::HIDDEN:
		case EGridBoundingBox::GRID_SIZE:

			localX = GridSize.X;
			localY = GridSize.Y;
			break;

		case EGridBoundingBox::GRIDBOUNDINGBOX_COUNT:
		default:

			UKismetSystemLibrary::PrintString(this, "Please make sure to set ShowHeightmapBoundingBox to a valid value (other than count)",
				true, true, FLinearColor::Red, 20.f);

			return;
		}
	}

	/* sets the scale and position depending on our heightmap setting and tilesize defined beforehand */
	outScale.X = localX * (TileSize.X / DefaultTileWidth);
	outScale.Y = localY * (TileSize.Y / DefaultTileWidth);
	outScale.Z = 0;

	outLocation.X = ((localX * TileSize.X) / 2) - (TileSize.X / 2);
	outLocation.Y = ((localY * TileSize.Y) / 2) - (TileSize.Y / 2);
	outLocation.Z = .1f;
}

void AGridManager::SetupHeightmapBox()
{
	check(HeightmapBounds);

	FVector location;
	FVector scale;

	/* rescale here to make sure the heightmap box is correctly set */
	ScaleCollisionAndHeightmapBoxes(false, FIntPoint(), location, scale);

	switch (Heightmap)
	{
	case EGridHeight::NONE:

		location.Z = 0.f;
		scale.Z = 0.f;
		break;


	case EGridHeight::ONE_LEVEL:
	case EGridHeight::MULTI_LEVEL:

		location.Z = (MaxHeight + MinHeight) / 2;
		scale.Z = (MaxHeight - MinHeight) / DefaultTileWidth;
		break;


	case EGridHeight::GRIDHEIGHT_COUNT:
	default:

		UKismetSystemLibrary::PrintString(this, "Please make sure to set Heightmap to a valid value (other than count)",
			true, true, FLinearColor::Red, 20.f);

		return;
	}

	/* depending on our height settings, only the Z axis will vary */
	HeightmapBounds->SetRelativeTransform(FTransform(FRotator(), location, scale));
	HeightmapBounds->SetVisibility(ShowHeightmapBoundingBox != EGridBoundingBox::HIDDEN);

	SetupGridLineDisplay();
}

void AGridManager::SetupGridLineDisplay()
{
	check(GridDecal);

	GridDecal->SetVisibility(EnableGridLineDisplay);
	if (!EnableGridLineDisplay)
	{
		return;
	}

	FVector location;
	FVector scale;
	/* again, make sure that our stuff is correctly setup as we realy on it for the decal */
	ScaleCollisionAndHeightmapBoxes(false, FIntPoint(), location, scale);

	/* adjust the location and scale for the decal */
	location.Z = (MaxHeight + MinHeight) / 2.f;

	/* sets the rotator as 90 on pitch (FRotator(Pitch, Yaw, Roll)) */
	GridDecal->SetRelativeTransform(FTransform(
		FRotator(90, 0, 0),
		location,
		FVector(((MaxHeight - MinHeight) / DefaultTileWidth) * 2, scale.Y, scale.X)));

	/* create the instance and set the default value for our X and Y params to an arbitrary value */
	auto instance = GridDecal->CreateDynamicMaterialInstance();

	/* set a bunch of parameters from our material instance */
	instance->SetScalarParameterValue("X", GridSize.X);
	instance->SetScalarParameterValue("Y", GridSize.Y);
	instance->SetScalarParameterValue("Thickness", GridLineThickness);
	instance->SetVectorParameterValue("Color", GridLineColor);
	instance->SetScalarParameterValue("Opacity", GridLineOpacity);
}

bool AGridManager::SpawnTileGrid(bool bPrintWarning /*= true*/)
{
	DefaultTile->ClearInstances();
	GridTiles.Empty();

	if (!ShowDefaultTile || (GetGraphSize() == 0))
	{
		if (bPrintWarning)
		{
			UKismetSystemLibrary::PrintString(this, "AGridManager::SpawnTileGrid - Either ShowDefaultTile is set to false or GridSize.X (or Y) is set to 0");
		}

		return false;
	}

	TArray<FTransform> tilesTransforms;
	for (int i = 0; i < (GridSize.X * GridSize.Y); ++i)
	{
		tilesTransforms.Add(FTransform(GetDisplayTileLocationFromIndex(i, GridSize)));
	}

	DefaultTile->AddInstances(tilesTransforms, false);

	return true;
}

void AGridManager::ScaleAutoVolumes()
{
	for (auto volume : AutoScaledVolumes)
	{
		if (volume && volume->IsValidLowLevel())
		{
			volume->SetActorLocation(HeightmapBounds->Bounds.Origin);
			volume->SetActorScale3D(HeightmapBounds->Bounds.BoxExtent * 0.01f);
		}
	}
}

void AGridManager::SetupGridCollisions()
{
	if (ShowDefaultTile)
	{
		DefaultTile->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// ECC_GameTraceChannel1 is the PathTrace collision channel
	CollisionPlane->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, IsCollisionPlaneWalkable ? ECollisionResponse::ECR_Block : ECollisionResponse::ECR_Ignore);
}

bool AGridManager::CreateGridLocations(const int32& aStartIndex, const FIntPoint& aGridSize, const EGridHeight& aHeightType, bool bShouldPrintOnFailure /*= true*/)
{
	/* simple check to avoid useless tests and processing (as it is quite heavy) */
	if (aGridSize.GetMin() <= 0)
	{
		if (bShouldPrintOnFailure)
		{
			UKismetSystemLibrary::PrintString(this, "AGridManager::CreateGridLocations - Please make sure that the grid size (x or y) is higher than 0.", true,
				true, FLinearColor::Red, 20.f);
		}

		return false;
	}

	/* create the locations depending on our height setting */
	switch (aHeightType)
	{
	case EGridHeight::NONE:

		return CreateNoHeightLocations(aStartIndex, aGridSize, bShouldPrintOnFailure);

	case EGridHeight::ONE_LEVEL:

		return CreateSingleLevelLocations(aStartIndex, aGridSize, bShouldPrintOnFailure);

	case EGridHeight::MULTI_LEVEL:

		return CreateMultiLevelLocations(aStartIndex, aGridSize, bShouldPrintOnFailure);

	case EGridHeight::GRIDHEIGHT_COUNT:
	default:

		if (bShouldPrintOnFailure)
		{
			UKismetSystemLibrary::PrintString(this, "AGridManager::CreateGridLocations - Please set the HeightType to a valid value (other than count).", true,
				true, FLinearColor::Red, 20.f);
		}

		return false;
	}
}

bool AGridManager::CreateNoHeightLocations(const int32& aStartIndex, const FIntPoint& aGridSize, bool bShouldPrintOnFailure /*= true*/)
{
	/* get all indexes for a given rect */
	TArray<int32> tileIndexes = GetAllGridIndexesNaive(aStartIndex, aGridSize);

	for (auto tileIndex : tileIndexes)
	{
		/* sets the z value to 0 as we don't care about the height in this method */
		FVector location = ConvertTileIndexToLocationNaive(tileIndex);
		location.Z = 0;

		FBaseTile& tile = GridTiles.AddDefaulted_GetRef();
		tile.TileRef = tileIndex;
		tile.TileLocation = location;
	}

	return true;
}

bool AGridManager::CreateSingleLevelLocations(const int32& aStartIndex, const FIntPoint& aGridSize, bool bShouldPrintOnFailure /*= true*/)
{
	/* get all indexes for a given rect */
	TArray<int32> tileIndexes = GetAllGridIndexesNaive(aStartIndex, aGridSize);

	FVector start;
	FVector end;
	FHitResult hit;

	/* pretty much the same as the "noheight" version, we just add a single trace test to find the correct position */
	for (auto tileIndex : tileIndexes)
	{
		start = end = ConvertTileIndexToLocationNaive(tileIndex);
		start.Z = MaxHeight;
		end.Z = MinHeight;

		start = GetActorTransform().TransformPosition(start);
		end = GetActorTransform().TransformPosition(end);

		ECollisionChannel collisionChannel = UEngineTypes::ConvertToCollisionChannel(PathTraceChannel);
		if (GetWorld()->LineTraceSingleByChannel(hit, start, end, collisionChannel))
		{			
			FBaseTile& tile = GridTiles.AddDefaulted_GetRef();
			tile.TileRef = tileIndex;
			tile.TileLocation = GetActorTransform().InverseTransformPosition(hit.Location);
		}
	}

	return true;
}

bool AGridManager::CreateMultiLevelLocations(const int32& aStartIndex, const FIntPoint& aGridSize, bool bShouldPrintOnFailure /*= true*/)
{
	TArray<int32> tileIndexes = GetAllGridIndexesNaive(aStartIndex, aGridSize);

	FVector location;

	/* create the locations for the various heights possible (depends on the Max/min height and height between levels*/
	for (auto tileIndex : tileIndexes)
	{
		location = ConvertTileIndexToLocationNaive(tileIndex);
		location.Z = 0;
		CreateLocationsAndHeightmap(tileIndex, location);
	}

	return true;
}

void AGridManager::GenerateGridEdges()
{
	SetupBaseEdges();

	SetupEdgesUsingTerrain();
}

void AGridManager::GenerateSimpleCostMap()
{
}

void AGridManager::CreateLocationsAndHeightmap(const int32& aGridIndex, const FVector& aLocation)
{
	FVector traceStart = ConvertGridLocationToWorld(aLocation.X, aLocation.Y, MaxHeight);
	FVector traceEnd = ConvertGridLocationToWorld(aLocation.X, aLocation.Y, MinHeight);

	FVector lastHitPosition(0, 0, -9999999);

	/* call the recursive function with defaults trace start/end positions and setup the last hit position to "random" value */
	CreateLocationsAndHeightmap_Recursive(aGridIndex, traceStart, traceEnd, lastHitPosition);
}

void AGridManager::UpdateHeightmapCache(const int32& aGridIndex)
{
	FGridNestedIntArray& nestedArray = HeightmapLevels.FindOrAdd(aGridIndex % IndexZ);
	nestedArray.Values.Add(aGridIndex / IndexZ);
}

TArray<FIntPoint>& AGridManager::SetupBaseEdges()
{
	BaseEdgesDirection.Empty();

	/* defines the 4 base direction (right, down, left, up) */
	BaseEdgesDirection.Add(FIntPoint(1, 0));
	BaseEdgesDirection.Add(FIntPoint(0, -1));
	BaseEdgesDirection.Add(FIntPoint(-1, 0));
	BaseEdgesDirection.Add(FIntPoint(0, 1));

	/* incase we use diagonal movement, add the specific cases (up right, down right, down left, up left) */
	if (UseDiagonalMovement)
	{
		BaseEdgesDirection.Add(FIntPoint(1, 1));
		BaseEdgesDirection.Add(FIntPoint(-1, 1));
		BaseEdgesDirection.Add(FIntPoint(-1, -1));
		BaseEdgesDirection.Add(FIntPoint(1, -1));
	}

	return BaseEdgesDirection;
}

void AGridManager::SetupEdgesUsingTerrain(bool bPrintOnError /*= true*/)
{
	/* avoid unnecessary processing if the heightmap is invalid */
	if (Heightmap == EGridHeight::GRIDHEIGHT_COUNT && bPrintOnError)
	{
		UKismetSystemLibrary::PrintString(this, "AGridManager::SetupEdgesUsingTerrain - Please ensure that Heighmap is set correctly (other than count).",
			true, true, FLinearColor::Red, 20.f);

		return;
	}

	/* lambda function for adding tile edges based on heightmap type */
	auto AddTileEdges = [&](int anIndex)
		{
			switch (Heightmap)
			{
			case EGridHeight::NONE:
				AddTileEdgesNoHeightmap(anIndex, ShouldTraceForWalls);
				break;

			case EGridHeight::ONE_LEVEL:
				AddTileEdgesOneLevelHeightmap(anIndex, ShouldTraceForWalls);
				break;

			case EGridHeight::MULTI_LEVEL:
				AddTileEdgesMultiLevelHeightmap(anIndex, ShouldTraceForWalls);
				break;

			default:
				break;
			}
		};

	int numIterations = (Heightmap != EGridHeight::MULTI_LEVEL) ? GridTiles.Num() : HeightmapLevels.Num();

	/* iterate through the grid locations and add tile edges based on heightmap type */
	for (int i = 0; i < numIterations; ++i)
	{
		AddTileEdges(i);
	}
}

void AGridManager::AddTileEdgesNoHeightmap(const int32& aGridIndex, bool bShouldTraceForWalls, bool bPrintOnError)
{
	/* get the tile we are testing edges for */
	FBaseTile& currentTile = GetTileFromIndex(aGridIndex);

	/* test the possible neighbours on each direction (starting with the "non diagonal" ones) */
	for (int edge = 0; edge < BaseEdgesDirection.Num(); ++edge)
	{
		int32 x = GetXComponent(aGridIndex) + BaseEdgesDirection[edge].X;
		int32 y = GetYComponent(aGridIndex) + BaseEdgesDirection[edge].Y;
		if (!IsIndexValid(x, y) || currentTile.HasValidEdgeAlongDirection(edge))
			continue;

		int32 neighbourIndex = x * GridSize.X + y;
		if (bShouldTraceForWalls && TraceOnGrid(aGridIndex, neighbourIndex, WallTraceChannel, WallTraceHeight))
			continue;

		FBaseTile& neighbourTile = GetTileFromIndex(neighbourIndex);
		currentTile.AddEdgeAlongDirection(edge, neighbourTile.DefaultCost + 1);
		neighbourTile.AddEdgeAlongDirection((edge + 2) % BaseEdgesDirection.Num(), currentTile.DefaultCost + 1);

	}
}

void AGridManager::AddTileEdgesOneLevelHeightmap(const int32& aGridIndex, bool bShouldTraceForWalls, bool bPrintOnError)
{
	/* get the tile we are looking edges for */
	FBaseTile& currentTile = GetTileFromIndex(aGridIndex);

	for (int edgeDirection = 0; edgeDirection < BaseEdgesDirection.Num(); ++edgeDirection)
	{
		int32 x = GetXComponent(aGridIndex) + BaseEdgesDirection[edgeDirection].X;
		int32 y = GetYComponent(aGridIndex) + BaseEdgesDirection[edgeDirection].Y;
		if (!IsIndexValid(x, y) || currentTile.HasValidEdgeAlongDirection(edgeDirection))
			continue;

		int32 neighbourIndex = x * GridSize.X + y;
		FBaseTile& neighbourTile = GetTileFromIndex(neighbourIndex);

		/* compares the cost to 0 incase we change it later on (add some "error codes" or whatever) */
		float cost = GetEdgeCostFromZDifference(currentTile.TileLocation.Z, neighbourTile.TileLocation.Z);
		if (cost <= 0)
			continue;

		/* check if there is any wall between the current tile and the targeted one */
		if (bShouldTraceForWalls && TraceOnGrid(aGridIndex, neighbourIndex, WallTraceChannel, WallTraceHeight))
			continue;

		/* sets for both tiles that there is a valid connection in the corresponding direction */
		currentTile.AddEdgeAlongDirection(edgeDirection, cost + neighbourTile.DefaultCost);
		neighbourTile.AddEdgeAlongDirection((edgeDirection + 2) % BaseEdgesDirection.Num(), cost + currentTile.DefaultCost);
	}
}

void AGridManager::AddTileEdgesMultiLevelHeightmap(const int32& aGridIndex, bool bShouldTraceForWalls, bool bPrintOnError)
{	
	/* get the tile we are looking edges for */
	FBaseTile& currentTile = GetTileFromIndex(aGridIndex);

	/* TBD */
}

void AGridManager::SetupGridArrays()
{
	CreateGridLocations(0, GridSize, Heightmap);

	GenerateGridEdges();

	GenerateSimpleCostMap();
}

void AGridManager::DebugPregenerateGameplayGrids()
{
	if (DebugDisplayTileIndexes)
		DisplayTileIndexes();

	if (DebugDisplayTileEdges)
		DisplayTileEdges();
}

void AGridManager::DisplayTileIndexes()
{
	for (const auto& tile : GridTiles)
	{
		FString text;

		text.Append("Tile index = " + FString::FromInt(tile.TileRef) + '\n');
		text.Append("X = " + FString::FromInt(GetXComponent(tile.TileRef)) + " Y = " + FString::FromInt(GetYComponent(tile.TileRef)));
		if (GridSizeZ > 1)
			text.Append(" Z = " + FString::FromInt(GetZComponent(tile.TileRef)));

		SpawnTileDebugText(tile, text);
	}
}

void AGridManager::DisplayTileEdges()
{
	/* either clear the current instances or create the object with the default mesh */
	if (EdgeMeshInstances)
	{
		EdgeMeshInstances->ClearInstances();
	}
	else
	{
		EdgeMeshInstances = NewObject<UInstancedStaticMeshComponent>(this);
		EdgeMeshInstances->SetStaticMesh(EdgeArrowMesh);
	}

	/* reset the mesh position, incase the grid moved */
	EdgeMeshInstances->SetRelativeLocation(GetActorLocation());

	for (const auto& currentTile : GridTiles)
	{
		for (int edgeDirection = 0; edgeDirection < BaseEdgesDirection.Num(); ++edgeDirection)
		{
			if (!currentTile.HasValidEdgeAlongDirection(edgeDirection))
				continue;

			int x = GetXComponent(currentTile.TileRef) + BaseEdgesDirection[edgeDirection].X;
			int y = GetYComponent(currentTile.TileRef) + BaseEdgesDirection[edgeDirection].Y;
			FBaseTile& neighbourTile = GetTileFromIndex(x * GridSize.X + y);

			FVector lookAtDir = neighbourTile.TileLocation - currentTile.TileLocation;
			lookAtDir.Normalize();

			FVector location = currentTile.TileLocation + (lookAtDir * TileSize.X / 3);
			location.Z += 10.f;

			EdgeMeshInstances->AddInstance(FTransform(lookAtDir.Rotation(), location, FVector(1.f, 1.f, 1.f)));
		}
	}
}

void AGridManager::SpawnTileDebugText(const FBaseTile& aTile, const FString& aText)
{
	FTransform transform(FRotator(90, 0, 270));
	transform.SetLocation(FVector(aTile.TileLocation.X, aTile.TileLocation.Y, aTile.TileLocation.Z + 10.f));
	transform.SetScale3D(FVector(0.7f, 0.7f, 0.7f));

	UTextRenderComponent* textComp = Cast<UTextRenderComponent>(AddComponentByClass(UTextRenderComponent::StaticClass(), false, transform, false));
	check(textComp);
	textComp->SetText(FText::FromString(aText));
}

void AGridManager::CreateLocationsAndHeightmap_Recursive(const int32& aGridIndex, FVector& aTraceStart, FVector& aTraceEnd, FVector& aLastHitPosition)
{
	FHitResult hit;
	ECollisionChannel collisionChannel = UEngineTypes::ConvertToCollisionChannel(PathTraceChannel);

	/* if we hit something.. */
	if (GetWorld()->LineTraceSingleByChannel(hit, aTraceStart, aTraceEnd, collisionChannel))
	{
		/* ... check first if it's in an acceptable range depending on the heigh between levels that is set */
		float abs = FMath::Abs(aLastHitPosition.Z - hit.Location.Z);
		aLastHitPosition = hit.Location;
		if (abs >= HeightBetweenLevels)
		{
			/* ... then reset our trace positions */
			aTraceStart = GetActorUpVector() * GetActorScale3D() + aLastHitPosition;
			aTraceEnd = (GetActorUpVector() * GetActorScale3D() * HeightBetweenLevels) + aLastHitPosition;

			/* try to find another hit */
			if (!GetWorld()->LineTraceSingleByChannel(hit, aTraceStart, aTraceEnd, collisionChannel))
			{
				/* but if we don't find anything, set this location in our heightmap */
				int idx = ConvertLocationToIndex3DNaive(aLastHitPosition);

				FBaseTile& tile = GridTiles.AddDefaulted_GetRef();
				tile.TileRef = idx;
				tile.TileLocation = GetActorTransform().InverseTransformPosition(aLastHitPosition);

				UpdateHeightmapCache(aGridIndex);

				GridSizeZ = FMath::Max((idx / IndexZ) + 1, GridSizeZ);
			}

			/* if we can go lower, try it */
			if (aLastHitPosition.Z >= (HeightBetweenLevels + MinHeight))
			{
				aTraceStart.Z = aLastHitPosition.Z - HeightBetweenLevels;
				CreateLocationsAndHeightmap_Recursive(aGridIndex, aTraceStart, aTraceEnd, aLastHitPosition);
			}
		}
	}
}

#pragma endregion

#pragma region Utility

const FVector AGridManager::FindClosestTileToSnapTo(const FVector& aLocation) const
{
	const FVector& gridLocation = ConvertWorldLocationToGrid(aLocation);
	float x = FMath::Floor((gridLocation.X + TileSize.X / 2) / TileSize.X) * TileSize.X;
	float y = FMath::Floor((gridLocation.Y + TileSize.Y / 2) / TileSize.Y) * TileSize.Y;
	float z = FMath::Floor(gridLocation.Z / HeightBetweenLevels) * HeightBetweenLevels;

	return ConvertGridLocationToWorld(x, y, z);
}

bool AGridManager::TraceOnGrid(const int32& aStartIndex, const int32& aTargetIndex, const ETraceTypeQuery& aTraceChannel, const float& aTraceHeight) const
{
	FVector start, end;
	if (!GetOffsetedWorldLocationAtIndex(aStartIndex, aTraceHeight, start)
		|| !GetOffsetedWorldLocationAtIndex(aTargetIndex, aTraceHeight, end))
		return false;

	FHitResult hit;
	ECollisionChannel collisionChannel = UEngineTypes::ConvertToCollisionChannel(aTraceChannel);
	return GetWorld()->LineTraceSingleByChannel(hit, start, end, collisionChannel);
}

bool AGridManager::GetOffsetedWorldLocationAtIndex(const int32& aGridIndex, const float& anOffset, FVector& outWorldLocation) const
{
	if (IsIndexValid(aGridIndex))
	{
		const FBaseTile& tile = GetTileFromIndex(aGridIndex);
		FVector location = tile.TileLocation;
		outWorldLocation = GetActorTransform().InverseTransformPosition(FVector(location.X, location.Y, location.Z + anOffset));

		return true;
	}

	return false;
}

bool AGridManager::ContainsTile(const int32& aTileIndex) const
{
	const FBaseTile* tile = GridTiles.FindByPredicate([&](const FBaseTile& tile)
		{
			return tile.TileRef == aTileIndex;
		}) ;

	return (tile != nullptr);
}

bool AGridManager::ContainsTile(const FBaseTile& aTile) const
{
	const FBaseTile* tile = GridTiles.FindByPredicate([&](const FBaseTile& tile)
		{
			return tile == aTile;
		});

	return (tile != nullptr);
}

FBaseTile& AGridManager::GetTileFromIndex(const int32& anIndex)
{
	FBaseTile* tile = GridTiles.FindByPredicate([&](const FBaseTile& aTile)
		{
			return aTile.TileRef == anIndex;
		});

	return *tile;
}

const FBaseTile& AGridManager::GetTileFromIndex(const int32& anIndex) const
{
	const FBaseTile* tile = GridTiles.FindByPredicate([&](const FBaseTile& aTile)
		{
			return aTile.TileRef == anIndex;
		});

	return *tile;
}

bool AGridManager::IsIndexValid(const int32& anIndex) const
{
	int32 x = GetXComponent(anIndex);
	int32 y = GetYComponent(anIndex);

	return (x >= 0) && (y >= 0) && (x < GridSize.X) && (y < GridSize.Y);
}

bool AGridManager::IsIndexValid(const int32& aX, const int32& aY) const
{
	return (aX >= 0) && (aY >= 0) && (aX < GridSize.X) && (aY < GridSize.Y);
}

int AGridManager::GetEdgeCostFromZDifference(const float& aStartZ, const float& aTargetZ) const
{
	float abs = FMath::Abs(aStartZ - aTargetZ);

	/* returns 1 as a default cost */
	if (abs < HeightSlowIncrement)
		return 1;

	if (abs < HeightImpassableCutoff)
	{
		return FMath::Floor(abs / HeightSlowIncrement) + 1;
	}

	return -1;
}

bool AGridManager::GetNeighbourUsingDirection(const int32& aTileIndex, const int32& aDirection, FBaseTile& outNeighbourTile) const
{
	int32 x = GetXComponent(aTileIndex) + BaseEdgesDirection[aDirection].X;
	int32 y = GetYComponent(aTileIndex) + BaseEdgesDirection[aDirection].Y;

	if (!IsIndexValid(x, y))
		return false;

	outNeighbourTile = GetTileFromIndex(x * GridSize.X + y);
	return true;
}

bool AGridManager::GetNeighbourUsingDirection(const FBaseTile& aTile, const int32& aDirection, FBaseTile& outNeighbourTile) const
{
	int32 x = GetXComponent(aTile.TileRef) + BaseEdgesDirection[aDirection].X;
	int32 y = GetYComponent(aTile.TileRef) + BaseEdgesDirection[aDirection].Y;

	if (!IsIndexValid(x, y))
		return false;

	outNeighbourTile = GetTileFromIndex(x * GridSize.X + y);
	return true;
}

const FVector AGridManager::GetDisplayTileLocationFromIndex(const int32& anIndex, const FIntPoint& aSize) const
{
	/* math shenanigans to get the tile location depending on a given index */
	return FVector(((anIndex % aSize.X) * TileSize.X), (((anIndex / aSize.X) - ((anIndex / (aSize.X * aSize.Y)) * aSize.X)) * TileSize.Y), 0);
}

TArray<int32> AGridManager::GetAllGridIndexesNaive(const int32& aStartIndex, const FIntPoint& aGridSize)
{
	TArray<int> ret;

	for (int i = 0; i < aGridSize.X; ++i)
	{
		for (int j = 0; j < aGridSize.Y; ++j)
		{
			/* The start index will act as an offset in that case */
			ret.Add((i * GridSize.X) + j + aStartIndex);
		}
	}

	return ret;
}

FVector AGridManager::ConvertTileIndexToLocationNaive(const int32& aGridIndex) const
{
	/* math shenanigans to find the actual location given an index */
	return FVector((((aGridIndex / GridSize.X) % GridSize.X) * TileSize.X), ((aGridIndex % GridSize.X) * TileSize.Y), ((aGridIndex / IndexZ) * HeightBetweenLevels));
}

FVector AGridManager::ConvertGridLocationToWorld(const FVector& aGridLocation) const
{
	return GetActorTransform().TransformPosition(aGridLocation);
}

FVector AGridManager::ConvertGridLocationToWorld(const float& aX, const float& aY, const float& aZ) const
{
	return GetActorTransform().TransformPosition(FVector(aX, aY, aZ));
}

int32 AGridManager::ConvertLocationToIndex3DNaive(const FVector& aLocation) const
{
	FVector transformedLocation = GetActorTransform().InverseTransformPosition(aLocation);

	/* bunch of math stuff to get the closer index */

	int32 x = FMath::Floor((transformedLocation.X + (TileSize.X / 2)) / TileSize.X) * GridSize.X;
	int32 y = FMath::Floor((transformedLocation.Y + (TileSize.X / 2)) / TileSize.X);
	int32 index = x + y;

	/* specific case of the multi level, as we need to take into account the z part of the location */
	if (Heightmap == EGridHeight::MULTI_LEVEL)
	{
		int32 z = FMath::Floor((transformedLocation.Z + 0.01f - MinHeight) / HeightBetweenLevels) * IndexZ;
		index += z;
	}

	return index;
}

const FVector AGridManager::ConvertWorldLocationToGrid(const FVector& aWorldLocation) const
{
	return GetActorTransform().InverseTransformPosition(aWorldLocation);
}

const int AGridManager::GetXComponent(const int32& aGridIndex) const
{
	return aGridIndex / GridSize.X;
}

const int AGridManager::GetYComponent(const int32& aGridIndex) const
{
	return aGridIndex % GridSize.X;
}

const int AGridManager::GetZComponent(const int32& aGridIndex) const
{
	return aGridIndex / IndexZ;
}

#pragma endregion

#pragma region Accessors

EGridHeight AGridManager::GetHeighType() const
{
	return Heightmap;
}

float AGridManager::GetMinHeight() const
{
	return MinHeight;
}

float AGridManager::GetMaxHeight() const
{
	return MaxHeight;
}

float AGridManager::GetDefaultTileWidth() const
{
	return DefaultTileWidth;
}

UStaticMesh* AGridManager::GetDefaultTileMesh() const
{
	return DefaultTileMesh;
}

int32 AGridManager::GetGraphSize() const
{
	return GridSize.X * GridSize.Y;
}

FVector AGridManager::GetTileSize() const
{
	return FVector(TileSize.X, TileSize.Y, 0.5f);
}

#pragma endregion

#pragma optimize("", on)