// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SubGrid.generated.h"

class UBoxComponent;
class UGridAnchorComponent;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class FIREEMBLEM_API ASubGrid : public AActor
{
	GENERATED_BODY()
	
public:	

	ASubGrid();


	/********
	* Accessors
	********/

	/* Access to the sub grid size */
	UFUNCTION(BlueprintCallable)
	const FIntPoint& GetGridSize() const;

	/* Access to the relative grid index */
	UFUNCTION(BlueprintCallable)
	const int& GetRelativeGridIndex() const;


protected:

	/********
	* Super overrides
	********/

	virtual void OnConstruction(const FTransform& Transform) override;


	/********
	* Subgrid generation
	********/

	/* Adjust the heighmap bounds of this subgrid depending on the grid manager settings */
	UFUNCTION(BlueprintCallable)
	virtual void AdjustHeighmapBounds();

	/* Spawn the grid meshes depending on the previous setup (grid anchor, bounds, etc) */
	UFUNCTION(BlueprintCallable)
	virtual void SpawnGridMeshes();


protected:

	/* Size of the grid on the X and Y axis */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subgrid|Defaults")
	FIntPoint GridSize;

	/* Index of the grid in the grid manager, will be setup during the grid construction */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subgrid|Defaults")
	int RelativeGridIndex;

	/* Defines if this grid should show its bounds or not */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subgrid|Defaults")
	bool ShowBounds;

	/* Defines if the subgrid will spawn its meshes */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Subgrid|Defaults")
	bool ShouldSpawnGridMeshes;

	/* Grid height bounds */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	TObjectPtr<UBoxComponent> HeightmapBounds;

	/* Default tiles instanced mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	TObjectPtr<UHierarchicalInstancedStaticMeshComponent> DefaultTile;

	/* Each subgrid can have a specific mesh, but if null, it will use the default one defined in the grid manager */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	TObjectPtr<UStaticMesh> TileMeshOverride;

	/* Grid anchor component. Will be used to "anchor" the subgrid to the grid manager */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
	TObjectPtr<UGridAnchorComponent> GridAnchor;
};