// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/Tile/BaseTile.h"

/* change it to a variable that we can tweak in the editor/runtime ? */
#define ENABLE_GENERIC_ASTAR_LOGGING 0

#if ENABLE_GENERIC_ASTAR_LOGGING
	#define GENERIC_ASTAR_LOG(Verbosity, Format, ...) UE_LOG(LogAStar, Verbosity, Format, __VA_ARGS__)
#else
	#define GENERIC_ASTAR_LOG(...)
#endif

/**
* Defines base data (policy) for the generic A* algorithm.
*/
struct FIREEMBLEM_API FGenericAStarPolicy
{
	static const int32 TilePoolSize = 64;
	static const int32 OpenSetSize = 64;
	static const int32 MaxPathLengthError = 10000;
	static const bool ShouldReuseTilePoolInSubsequentSearches = false;
};


/*
 *	Filter class is what decides which graph edges can be used and at what cost. It needs to implement following functions:
 *		double GetHeuristicScale() const;
 *		double GetHeuristicCost(const FSearchNode& StartNode, const FSearchNode& EndNode) const;
 *		double GetTraversalCost(const FSearchNode& StartNode, const FSearchNode& EndNode) const;
 *		bool IsTraversalAllowed(const FNodeRef NodeA, const FNodeRef NodeB) const;
 *		bool AcceptPartialSolution() const;
 */
template<typename TSearchTile = FBaseTile>
struct FIREEMBLEM_API FGenericAStarQueryFilter
{
	/* Used as GetHeuristicCost's multiplier */
	virtual double GetHeuristicScale() const
	{
		double ret;
		switch (Heuristic)
		{
		case EGraphAStarHeuristic::DEFAULT:
			ret = 1;
			break;

		case EGraphAStarHeuristic::MANHATTAN:
			ret = 1;
			break;

		default:
			GENERIC_ASTAR_LOG(Error, TEXT("Please make sure that filters use a correct heuristic (other than count)."));
			break;
		}

		return ret;
	}

	/* Estimates the cost from aStartTile to go to a specific direction */
	virtual double GetHeuristicCost(const TSearchTile& aStartTile, const int& aDirection) const
	{
		return GetHeuristicScale() * GetTraversalCost(aStartTile, aDirection);
	}

	/* Calculate the real cost to travel from aStartTile directly to anEndTile */
	virtual double GetTraversalCost(const TSearchTile& aStartTile, const int& aDirection) const
	{
		/* for now return 0 if the node doesn't have an edge along a given direction */
		if (aStartTile.HasEdgeAlongDirection(aDirection))
			return aStartTile.GetEdgeCostAlongDirection(aDirection);
		else
			return 0;
	}

	/* Returns if we can go from aATile to aBTile */
	virtual bool IsTraversalAllowed(const TSearchTile& aATile, const TSearchTile& aBTile) const
	{
		return aBTile.IsTileBlocked();
	}

	/* Defines if the filter can accept solutions that do not reach the goal */
	virtual bool AcceptPartialSolution() const
	{
		return ShouldAcceptPartialSolution;
	}


	/********
	* Members
	********/

	/* Defines if the filter can accept solutions that do not reach the goal */
	bool ShouldAcceptPartialSolution = true;

	/* Defines the heuristic that will be used by this filter */
	EGraphAStarHeuristic Heuristic;

	/* Defines the maximum value for a path (will be used for instance to find the nodes in range of another one) */
	double MaxPathCost;
};


/**
 *	Generic graph A* implementation
 *
 *		// Backward compatible methods, please use the FSearchNode version. If the FSearchNode version are implemented, these methods will not be called at all.
 *		FNodeRef GetNeighbour(const FNodeRef NodeRef, const int32 NeighbourIndex) const;					- returns neighbour ref
 *		FVector::FReal GetHeuristicCost(const FNodeRef StartNodeRef, const FNodeRef EndNodeRef) const;		- estimate of cost from StartNode to EndNode from a NodeRef
 *		FVector::FReal GetTraversalCost(const FNodeRef StartNodeRef, const FNodeRef EndNodeRef) const;		- real cost of traveling from StartNode directly to EndNode from a NodeRef
 *
 *		// Optionally implemented methods to parameterize the search
 *		int32 GetNeighbourCount(FNodeRef NodeRef) const;													- returns number of neighbours that the graph node identified with NodeRef has, it is ok if not implemented, the logic will stop calling GetNeighbour once it received an invalid noderef
 *		bool ShouldIgnoreClosedNodes() const;																- whether to revisit closed node or not
 *		bool ShouldIncludeStartNodeInPath() const;															- whether to put the start node in the resulting path
 *		int32 GetMaxSearchNodes() const;																	- whether to limit the number of search nodes to a maximum
 *		FVector::FReal GetCostLimit() const																	- whether to limit the search to a maximum cost
 */
template<typename TSearchTile = FBaseTile, typename Policy = FGenericAStarPolicy>
struct FIREEMBLEM_API FGenericAStar
{
	using FTileArray = TArray<TSearchTile>;

	struct FTilePool : FTileArray
	{
	};

	template<typename TQueryFilter = FGenericAStarQueryFilter, typename TResultPathInfo = TArray<TSearchTile>>
	EGraphAStarResult FindPath(const TSearchTile& aStartTile, const TSearchTile& anEndTile, const TQueryFilter& aFilter, TResultPathInfo& outPath)
	{
		return EGraphAStarResult::SEARCH_FAIL;
	}

	template<typename TQueryFilter = FGenericAStarQueryFilter, typename TResultTiles = TArray<TSearchTile>>
	void FindTilesInRange(const TSearchTile& aStartTile, const TQueryFilter& aFilter, TResultTiles& outTiles)
	{
	}
};