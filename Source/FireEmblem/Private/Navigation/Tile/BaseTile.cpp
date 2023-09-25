// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/Tile/BaseTile.h"

bool FBaseTile::HasValidEdgeAlongDirection(const int& aDirection) const
{
	return (EdgesMask & (1 << aDirection)) != 0;
}

const int FBaseTile::GetEdgeCostAlongDirection(const int& aDirection) const
{
	if (!HasValidEdgeAlongDirection(aDirection))
		return -1;

	return EdgesCosts[aDirection];
}

void FBaseTile::AddEdgeAlongDirection(const int& aDirection, const int& anEdgeCost /*= 1*/, bool bShouldModifyIsAlreadyExisting /*= false*/)
{
	if (HasValidEdgeAlongDirection(aDirection))
	{
		if (bShouldModifyIsAlreadyExisting)
			EdgesCosts[aDirection] = anEdgeCost;

		return;
	}

	EdgesMask |= (1 << aDirection);
	EdgesCosts.Add(aDirection, anEdgeCost);
}

bool FBaseTile::RemoveEdgeAlongDirection(const int& aDirection)
{
	if (!HasValidEdgeAlongDirection(aDirection))
		return false;

	EdgesMask |= (0 << aDirection);
	EdgesCosts.Remove(aDirection);

	return true;
}

bool FBaseTile::ModifyEdgeCost(const int& aDirection, const int& aNewCost)
{
	if (!HasValidEdgeAlongDirection(aDirection))
		return false;

	EdgesCosts[aDirection] = aNewCost;

	return true;
}

bool operator==(const FBaseTile& aLeft, const FBaseTile& aRight)
{
	return aLeft.GridIndex == aRight.GridIndex;
}