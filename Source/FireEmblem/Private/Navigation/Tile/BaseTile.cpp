// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/Tile/BaseTile.h"

bool FBaseTile::HasValidEdgeAlongDirection(const int32& aDirection) const
{
	return (EdgesMask & (1 << aDirection)) != 0;
}

const int FBaseTile::GetEdgeCostAlongDirection(const int32& aDirection) const
{
	if (!HasValidEdgeAlongDirection(aDirection))
		return -1;

	return EdgesCosts[aDirection];
}

void FBaseTile::AddEdgeAlongDirection(const int32& aDirection, const int32& anEdgeCost /*= 1*/)
{
	EdgesMask |= (1 << aDirection);
	EdgesCosts.Add(aDirection, anEdgeCost);
}

bool FBaseTile::RemoveEdgeAlongDirection(const int32& aDirection)
{
	if (!HasValidEdgeAlongDirection(aDirection))
		return false;

	EdgesMask |= (0 << aDirection);
	EdgesCosts.Remove(aDirection);

	return true;
}

bool FBaseTile::ModifyEdgeCost(const int32& aDirection, const int32& aNewCost)
{
	if (!HasValidEdgeAlongDirection(aDirection))
		return false;

	EdgesCosts[aDirection] = aNewCost;

	return true;
}

bool FBaseTile::IsTileBlocked() const
{
	return bIsTileBlocked;
}

void FBaseTile::BlockTile()
{
	bIsTileBlocked = true;
}

void FBaseTile::FreeTile()
{
	bIsTileBlocked = false;
}

void FBaseTile::MarkOpen()
{
	IsTileOpen = true;
}

void FBaseTile::MarkNotOpen()
{
	IsTileOpen = false;
}

void FBaseTile::MarkClosed()
{
	IsTileClosed = true;
}

void FBaseTile::MarkNotClosed()
{
	IsTileClosed = false;
}

bool FBaseTile::IsOpened() const
{
	return IsTileOpen;
}

bool FBaseTile::IsClosed() const
{
	return IsTileClosed;
}

const int32 FBaseTile::GetNeighbourCount() const
{
	return EdgesCosts.Num();
}

int32 FBaseTile::GetNeighbourCount()
{
	return EdgesCosts.Num();
}

const TArray<int32> FBaseTile::GetNeighboursDirections() const
{
	TArray<int32> keys;
	EdgesCosts.GetKeys(keys);
	return keys;
}

TArray<int32> FBaseTile::GetNeighboursDirections()
{
	TArray<int32> keys;
	EdgesCosts.GetKeys(keys);
	return keys;
}

bool FBaseTile::operator==(const FBaseTile& anOther)
{
	return TileRef == anOther.TileRef;
}

bool operator==(const FBaseTile& aLeft, const FBaseTile& aRight)
{
	return aLeft.TileRef == aRight.TileRef;
}