// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTileEffect.h"
#include "BaseTile.generated.h"

/**
 * Default tile used by the grid logic and generic A*
 */
USTRUCT(Blueprintable)
struct FBaseTile
{
	GENERATED_BODY()

	/* Simple constructor and destructor */
	explicit FBaseTile()
		: TileRef(-1), ParentTileRef(-1), IsTileOpen(false), IsTileClosed(false)
	{
	}

	~FBaseTile()
	{
	}


	/********
	* Utility
	********/

	/* Returns if this tile has a valid connection along a specific direction */
	bool HasValidEdgeAlongDirection(const int32& aDirection) const;

	/* Returns the cost of a specific edge. 
	* If there is no connection in the specified direction, returns -1
	*/
	const int GetEdgeCostAlongDirection(const int32& aDirection) const;

	/* Add a new edge along a specific direction, with a default cost of 1
	* If the edge was already created, can modify the cost by setting bShouldModifyIsAlreadyExisting to true
	*/
	void AddEdgeAlongDirection(const int32& aDirection, const int32& anEdgeCost = 1);

	/* Removes an edge from the tile (depending on the direction) 
	* Returns if the edge was successfully removed (meaning that it went from valid to invalid)
	*/
	bool RemoveEdgeAlongDirection(const int32& aDirection);

	/* Modify the cost of a specific edge.
	* Return true if the cost was successfully modified (first, the connection needs to be valid)
	*/
	bool ModifyEdgeCost(const int32& aDirection, const int32& aNewCost);

	/* Returns if the tile is blocked or not */
	bool IsTileBlocked() const;

	/* Sets the tile as blocked */
	void BlockTile();

	/* Sets the tile as not blocked */
	void FreeTile();

	/* Modify the IsTileOpen flag, used by the generic pathfinder */
	void MarkOpen();
	void MarkNotOpen();

	/* Modify the IsTileClosed flag, used by the generic pathfinder */
	void MarkClosed();
	void MarkNotClosed();

	/* Access to the IsTileOpen flag */
	bool IsOpened() const;

	/* Access to the IsTileClosed flag */
	bool IsClosed() const;

	/* Returns the number of neighbours this tile have */
	const int32 GetNeighbourCount() const;
	int32 GetNeighbourCount();

	/* Returns all the directions of the neighbours of this tile */
	const TArray<int32> GetNeighboursDirections() const;
	TArray<int32> GetNeighboursDirections();

	/* Simple operator to know if 2 tiles are equals, mostly used by the grid manager */
	friend bool operator== (const FBaseTile& aLeft, const FBaseTile& aRight);
	bool operator== (const FBaseTile& anOther);


	/********
	* Members
	********/

	/* Tile location in world space */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector TileLocation = FVector();

	/* Index of the tile in the grid.
	* Is used by the generic A* implementation
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TileRef = 0;

	/* Sets the default cost to reach this tile. 
	* This can be override by effects, etc, and it will be added to the edge default cost to get the actual cost to get to this tile.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 DefaultCost = 0;

	/* Mask defining the tile connections */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 EdgesMask = 0;

	/* Map defining the cost for each edge (if there is a connection) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<int32, int32> EdgesCosts;

	/* List of effects related to the tile.
	* Could be empty, and need to find a way to properly ensure that effects can match together
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TObjectPtr<UBaseTileEffect>> TileEffects;

	/* Defines if the tile is blocked at a given time (by default, it shouldn't, but in case someone is standing on the tile, or an object/something is on the tile) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsTileBlocked = false;

	/* Total cost to reach this node. Used by the generic pathfinder */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCost = 0;

	/* Ref to the parent tile index, used by the generic pathfinder */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ParentTileRef;

	/* Used by the generic pathfinder */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 IsTileOpen : 1;

	/* Used by the generic pathfinder */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 IsTileClosed : 1;
};

/* This is added in order to have a basetile as tmap.key */
FORCEINLINE uint32 GetTypeHash(const FBaseTile& MidiTime)
{
	uint32 Hash = FCrc::MemCrc32(&MidiTime, sizeof(FBaseTile));
	return Hash;
}