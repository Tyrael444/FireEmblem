// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/Enum/GridEnums.h"

#define ENABLE_GENERIC_PATHFINDER_LOG 0
#if ENABLE_GENERIC_PATHFINDER_LOG
	#define GENERIC_PATHFINDER_LOG(Verbosity, Format) UE_LOG(Verbosity, Format, __VA_ARGS__)
#else
	#define GENERIC_PATHFINDER_LOG(...)
#endif

struct FBaseTile;

/* Defines base data for the pathfinding algorithms */
struct FGenericPathfinderPolicy
{
	/* defines the maximum length for our path before triggering an error */
	static const int32 PathMaxLength = 10000; 
};

struct FGenericPathfinderQueryFilter
{
	int32 GetMaxDistance() const
	{
		return MaxDistance;
	}

	int32 MaxDistance;
};

/**
 * 
 */
template<typename TGraph, typename TSearchTile = FBaseTile, typename Policy = FGenericPathfinderPolicy>
struct FIREEMBLEM_API FGenericPathfinder
{
	using FTileArray = TArray<TSearchTile>;

	struct FTileSorter
	{
		bool operator() (const TSearchTile& aA, const TSearchTile& aB)
		{
			return aA.TotalCost < aB.TotalCost;
		}

		bool operator() (TSearchTile& aA, TSearchTile& aB)
		{
			return aA.TotalCost < aB.TotalCost;
		}
	};

	struct FPriorityQueue : FTileArray
	{
		typedef FTileArray Super;

		const FTileSorter& TileSorter;

		FPriorityQueue(const FTileSorter& aSorter)
			: TileSorter{ aSorter }
		{
		}

		void Push(const TSearchTile& aSearchTile)
		{
			//Super::HeapPush(aSearchTile, TileSorter);
			Super::HeapPush(aSearchTile, [aSearchTile](const TSearchTile&, const TSearchTile& aTile) {
				return aSearchTile.TotalCost < aTile.TotalCost; });
		}

		TSearchTile Pop()
		{
			check(Super::Num() > 0);
			TSearchTile tile;
			//Super::HeapPop(tile, TileSorter, false);
			Super::HeapPop(tile, [](const TSearchTile& aA, const TSearchTile& aB) {
				return aA.TotalCost < aB.TotalCost;
				}, false);
			return tile;
		}
	};

	template<typename TGraph>
	FGenericPathfinder(const TGraph& aGraph)
		: Graph(aGraph), PriorityQueue(TileSorter)
	{
	}

	/* Uses a Djikstra to find all the tiles in a given range, starting from aStartTile */
	template<typename TQueryFilter, typename TResultTiles = TArray<TSearchTile>>
	void GetTilesInRange(const TSearchTile& aStartTile, const TQueryFilter& aFilter, TResultTiles& outTilesInRange)
	{
		GENERIC_PATHFINDER_LOG(Display, TEXT(""));
		GENERIC_PATHFINDER_LOG(Display, TEXT("Starting GetTilesInRange request..."));

		if (!Graph.ContainsTile(aStartTile))
		{
			GENERIC_PATHFINDER_LOG(Error, TEXT("Graph doesn't contain the starting tile"));
			return;
		}

		TMap<TSearchTile, int> distance;
		distance.Add(aStartTile, 0);
		PriorityQueue.Push(aStartTile);

		while (!PriorityQueue.IsEmpty())
		{
			TSearchTile currentTile = PriorityQueue.Pop();
			int32 currentDistance = currentTile.TotalCost;

			if (currentDistance > aFilter.GetMaxDistance())
				break;

			for (int direction = 0; direction < currentTile.GetNeighbourCount(); ++direction)
			{
				int cost = currentTile.GetEdgeCostAlongDirection(direction);
				int neighbourDistance = currentDistance + cost;
				TSearchTile neighbourTile;
				bool res = Graph.GetNeighbourUsingDirection(currentTile.TileRef, direction, neighbourTile);
				if (!res)
					continue;

				if (!distance.Contains(neighbourTile) || neighbourDistance < distance[neighbourTile])
				{
					if (distance.Contains(neighbourTile))
						distance[neighbourTile] = neighbourDistance;
					else
						distance.Add(neighbourTile, neighbourDistance);

					neighbourTile.ParentTileRef = currentTile.TileRef;
					neighbourTile.TotalCost = neighbourDistance;
					PriorityQueue.Push(neighbourTile);
				}
			}
		}

		for (auto& pair : distance)
		{
			if (pair.Value <= aFilter.GetMaxDistance())
				outTilesInRange.Add(pair.Key);
		}
	}

	/* Runs an A* to find a path from aStartTile to anEndTile */
	template<typename TQueryFilter, typename TResultPath = TArray<TSearchTile>>
	EGraphAStarResult FindPath_AStar(const TSearchTile& aStartTile, const TSearchTile& anEndTile, const TQueryFilter& aFilter, TResultPath& outPath)
	{
		GENERIC_PATHFINDER_LOG(Display, TEXT(""));
		GENERIC_PATHFINDER_LOG(Display, TEXT("Starting FindPath_AStar request..."));

		if (!Graph.ContainsTile(aStartTile) || !Graph.ContainsTile(anEndTile))
			return EGraphAStarResult::SEARCH_FAIL;

		if (aStartTile.TileRef == anEndTile.TileRef)
			return EGraphAStarResult::SEARCH_SUCCESS;

		EGraphAStarResult result = EGraphAStarResult::SEARCH_SUCCESS;

		return result;
	}

	/* Runs a Djikstra to find a path from aStartTile to anEndTile */
	template<typename TQueryFilter, typename TResultPath = TArray<TSearchTile>>
	EGraphAStarResult FindPath_Dijkstra(const TSearchTile& aStartTile, const TSearchTile& anEndTile, const TQueryFilter& aFilter, TResultPath& outPath)
	{
		GENERIC_PATHFINDER_LOG(Display, TEXT(""));
		GENERIC_PATHFINDER_LOG(Display, TEXT("Starting FindPath_Dijkstra request..."));

		if (!Graph.ContainsTile(aStartTile) || !Graph.ContainsTile(anEndTile))
			return EGraphAStarResult::SEARCH_FAIL;

		if (aStartTile.TileRef == anEndTile.TileRef)
			return EGraphAStarResult::SEARCH_SUCCESS;

		EGraphAStarResult result = EGraphAStarResult::SEARCH_SUCCESS;

		return result;
	}


	/********
	* Members
	********/

	const TGraph& Graph;

	FPriorityQueue PriorityQueue;
	FTileSorter TileSorter;
};