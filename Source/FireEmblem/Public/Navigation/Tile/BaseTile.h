// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTileEffect.h"
#include "BaseTile.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBaseTile
{
	GENERATED_BODY()

public:

	/********
	* Utility
	********/

	/* Returns if this tile has a valid connection along a specific direction */
	bool HasValidEdgeAlongDirection(const int& aDirection) const;

	/* Returns the cost of a specific edge. 
	* If there is no connection in the specified direction, returns -1
	*/
	const int GetEdgeCostAlongDirection(const int& aDirection) const;

	/* Add a new edge along a specific direction, with a default cost of 1
	* If the edge was already created, can modify the cost by setting bShouldModifyIsAlreadyExisting to true
	*/
	void AddEdgeAlongDirection(const int& aDirection, const int& anEdgeCost = 1, bool bShouldModifyIsAlreadyExisting = false);

	/* Removes an edge from the tile (depending on the direction) 
	* Returns if the edge was successfully removed (meaning that it went from valid to invalid)
	*/
	bool RemoveEdgeAlongDirection(const int& aDirection);

	/* Modify the cost of a specific edge.
	* Return true if the cost was successfully modified (first, the connection needs to be valid)
	*/
	bool ModifyEdgeCost(const int& aDirection, const int& aNewCost);

	/* Simple operator to know if 2 tiles are equals, mostly used by the grid manager */
	friend bool operator== (const FBaseTile& aLeft, const FBaseTile& aRight);


public:

	/* Tile location in world space */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TileLocation = FVector();

	/* Index of the tile in the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int GridIndex = 0;

	/* Mask defining the tile connections */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int EdgesMask = 0;

	/* Map defining the cost for each edge (if there is a connection) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int, int> EdgesCosts;

	/* List of effects related to the tile.
	* Could be empty, and need to find a way to properly ensure that effects can match together
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UBaseTileEffect>> TileEffects;
};