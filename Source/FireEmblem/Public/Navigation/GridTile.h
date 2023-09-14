// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridTile.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGridTile
{
	GENERATED_BODY()

public:

	/* Default constructor */
	FGridTile();

	/* Defines the tile index in the grid */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int GridIndex;

	/* Defines the tile world position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector WorldPosition;

	/* Defines the cost to walk to this tile */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Cost;

	/* Defines the neighbours for this tile. Each direction will be set to 0 or 1 on the mask (up, down, left, right) 
	* Maybe plan for diagonals later ? as other bits for the mask
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int NeighbourMask;

	/* Defines the tile walkability (aka, mobility type: if can be walked on by flying only, any type, etc) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int WalkableMask;
};