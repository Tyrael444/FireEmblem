// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/GridTile.h"

FGridTile::FGridTile()
	:	GridIndex(0),
		WorldPosition(),
		Cost(0),
		NeighbourMask(0),
		WalkableMask(0)
{
}