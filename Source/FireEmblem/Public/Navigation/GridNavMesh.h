// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.h"
#include "Enums/FEEnum.h"
#include "GridNavMesh.generated.h"

class AGridBoundsVolume;

USTRUCT(BlueprintType)
struct FGridTileMeshData
{
	GENERATED_BODY()

public:

	/* Defines the mesh that will be used for the grid tiles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> TileMesh;

	/* Defines the material for the border of the tile mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> TileBorderMaterial;

	/* Defines the material to fill the tile mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> TileFillMaterial;

	/* Defines the default size for the tile mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector TileMeshSize;
};

UCLASS(config = Engine, defaultconfig, hidecategories = (Input, Rendering, Tags, Transformation, Actor, Layers, Replication))
class FIREEMBLEM_API AGridNavMesh : public AActor
{
	GENERATED_BODY()

public:

	// Sets default values for this actor's properties
	AGridNavMesh();

	virtual void BeginPlay() override;

	/* Starts the scanning process */
	UFUNCTION(CallInEditor, Category = "Grid NavMesh")
	void Scan();

	UFUNCTION(BlueprintCallable)
	void DrawTiles() const;


protected:

	/* This will setup basic data, like the bottom left position, etc; before actualling creating the grid */
	UFUNCTION()
	void SetupGrid();

	/* Create all the tiles needed for this grid.
	* This will only create tiles that are within the gridboundsvolume.
	*/
	UFUNCTION()
	void CreateTiles();

	/* Clear the tiles array */
	UFUNCTION(CallInEditor, Category = "Grid NavMesh")
	void ClearTiles();

	/* Calculate all the tiles positions (calculate exact world location, defines if walkable, etc).
	* Make sure to call CalculateTilesConnections() afterwards to properly update the tiles connections
	*/
	UFUNCTION()
	void CalculateTilesPositions();

	/* Recalculate a single tile position, walkability, etc 
	* If you call this, make sure to call CalculateTileConnections() on the same tile afterwards to update the tiles connections
	*/
	UFUNCTION()
	void CalculateTile(int aXIndex, int aYIndex);

	/* This will calculate the connections for all the graph tiles */
	UFUNCTION()
	void CalculateTilesConnections();

	/* Calculate a single tile connections */
	UFUNCTION()
	void CalculateTileConnections(int aXIndex, int aYIndex);

	/* Simple function to test various entries and data before doing anything in the scanning process. 
	* Return false if something is wrong
	*/
	UFUNCTION()
	bool PerformSanityCheck();

	/* Test if a connection is possible between the two tiles */
	UFUNCTION()
	bool IsConnectionValid(const FGridTile& aTile, const FGridTile& aPossibleNeighbour) const;

	/* Return a ref to a neighbour depending on the direction.
	* This will return false if no neighbour in the direction
	*/
	UFUNCTION()
	bool GetNeighbourAlongDirection(const FGridTile& aTile, int aDirection, FGridTile& outNeighbour) const;

protected:

	/* Defines the generation method. Either using bounds, or a center point */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation Parameters")
	EFEGridGenerationMethod GenerationMethod;

	/* Defines the grid bounds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation Parameters", meta = (EditCondition = "GenerationMethod == EFEGridGenerationMethod::BOUNDS", EditConditionHides))
	TObjectPtr<AGridBoundsVolume> GridBounds;

	/* Array containing all the tiles for this grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tiles")
	TArray<FGridTile> Tiles;

	/* Channel use when tracing for tiles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation Parameters")
	TEnumAsByte<ECollisionChannel> ECC_GridMeshWalkable;

	/* Defines the tile count on the x and y axis */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation Parameters")
	FIntPoint TileCount;

	/* Defines the size for each tile */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation Parameters")
	FVector TileSize;

	/* Defines the length for the trace that will be added to the tile location in order to find the ground */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generation Parameters")
	float TraceLength = 500.f;

	/* Defines the agent radius, will be used for the generation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Agent", meta = (UIMin = "0"))
	float AgentRadius;

	/* Defines the agent max slope */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Agent", meta = (UIMin = "0", UIMax = "90"))
	float AgentMaxSlope;

	/* Defines if we should enable or not virtual tiles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tiles")
	bool ShouldEnableVirtualTiles = false;

	/* Access to the bottom left position of the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generation Parameters")
	FVector BottomLeftPosition;

	/* Defines the offset for the X axis on the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> NeighbourXOffsets;

	/* Defines the offset for the Y axis on the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> NeighbourYOffsets;

	/* Defines the offset for the neighbours */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<int> NeighbourOffset;

	/* Defines the mesh data that will be used for our tiles */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tiles")
	FGridTileMeshData MeshData;

	/* Instance mesh for the tiles */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInstancedStaticMeshComponent> TileMeshes;
};