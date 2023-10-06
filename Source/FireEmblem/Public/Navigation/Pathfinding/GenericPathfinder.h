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

	bool ShouldIncludeStartTile() const
	{
		return bShouldIncludeStartTile;
	}

	int32 MaxDistance;
	bool bShouldIncludeStartTile;
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
	FGenericPathfinder(TGraph& aGraph)
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

		/* Reset all tiles cost and the priority queue */
		Graph.ResetAllTiles();
		PriorityQueue.Empty();

		TMap<TSearchTile, int> distance;
		distance.Add(aStartTile, 0);
		PriorityQueue.Push(aStartTile);

		while (!PriorityQueue.IsEmpty())
		{
			TSearchTile currentTile = PriorityQueue.Pop();
			int currentDistance = currentTile.TotalCost;

			if (currentDistance > aFilter.GetMaxDistance())
				break;

			/* no tiles should have no neighbours, they should have been removed from the grid earlier */
			check(currentTile.GetNeighbourCount() > 0);

			for (auto& direction : currentTile.GetNeighboursDirections())
			{
				int cost = currentTile.GetEdgeCostAlongDirection(direction);
				int neighbourDistance = currentDistance + cost;

				/* do we need to test for a valid neighbour ? */
				TSearchTile& neighbourTile = Graph.GetNeighbourUsingDirection_Unsafe(currentTile.TileRef, direction);

				if (!distance.Contains(neighbourTile) || neighbourDistance < distance[neighbourTile])
				{
					distance.FindOrAdd(neighbourTile) = neighbourDistance;
					neighbourTile.ParentTileRef = currentTile.TileRef;
					neighbourTile.TotalCost = neighbourDistance;
					PriorityQueue.Push(neighbourTile);
				}
			}
		}

		for (const auto& pair : distance)
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

		/* Reset all tiles cost */
		Graph.ResetAllTiles();

		TMap<TSearchTile, int> distance;
		distance.Add(aStartTile, 0);
		PriorityQueue.Push(aStartTile);

		/* simple dijkstra algo */
		while (!PriorityQueue.IsEmpty())
		{
			TSearchTile currentTile = PriorityQueue.Pop();
			/* no tiles should have no neighbours, they should have been removed from the grid earlier */
			check(currentTile.GetNeighbourCount() > 0);

			int currentDistance = currentTile.TotalCost;

			/* avoid too long paths, just a safety */
			if (currentDistance >= Policy::PathMaxLength)
			{
				result = EGraphAStarResult::INFINITE_LOOP;
				break;
			}

			for (auto& direction : currentTile.GetNeighboursDirections())
			{
				int cost = currentTile.GetEdgeCostAlongDirection(direction);
				int neighbourDistance = currentDistance + cost;

				/* do we need to test for a valid neighbour ? */
				TSearchTile& neighbourTile = Graph.GetNeighbourUsingDirection_Unsafe(currentTile.TileRef, direction);

				if (!distance.Contains(neighbourTile) || neighbourDistance < distance[neighbourTile])
				{
					distance.FindOrAdd(neighbourTile) = neighbourDistance;
					neighbourTile.ParentTileRef = currentTile.TileRef;
					neighbourTile.TotalCost = neighbourDistance;
					PriorityQueue.Push(neighbourTile);
				}
			}
		}

		/* check if the goal is reachable */
		if (!distance.Contains(anEndTile))
		{
			return EGraphAStarResult::UNREACHABLE_GOAL;
		}

		/* reverse the path */
		int parent = anEndTile.TileRef;
		while (parent != -1)
		{
			if (parent == aStartTile.TileRef && !aFilter.ShouldIncludeStartTile())
				break;

			outPath.Add(Graph.GetTileFromIndex(parent));
			parent = anEndTile.ParentTileRef;
		}

		return result;
	}


	/********
	* Members
	********/

	TGraph& Graph;

	FPriorityQueue PriorityQueue;
	FTileSorter TileSorter;
};