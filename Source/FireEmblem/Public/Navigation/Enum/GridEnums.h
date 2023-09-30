// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGridBoundingBox : uint8
{
	HIDDEN					UMETA(DisplayName = "Hidden"),
	GRID_SIZE				UMETA(DisplayName = "By Grid Size"),

	GRIDBOUNDINGBOX_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGridHeight : uint8
{
	NONE				UMETA(DisplayName = "None", Tooltip = "Means that it doesn't use the height feature"),
	ONE_LEVEL			UMETA(DisplayName = "One level", Tooltip = "Traces from the sky (at MaxGridHeight) to the center of each tile once to generate a single layer heightmap"),
	MULTI_LEVEL			UMETA(DisplayName = "Multilevel", Tooltip = "Traces from sky to each tile center, then continues downward and adds a level for each level found that is further from the previous than HeightBetweenLevels until MaxLevels or MinGridHeight is reached"),

	GRIDHEIGHT_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGridTileEffect : uint8
{
	BUFF_ALL				UMETA(DisplayName = "Buff", Tooltip = "This effect will provide a buff to the tile and will affect everyone. Incompatible with the debuff effect"),
	DEBUFF_ALL				UMETA(DisplayName = "Debuff", Tooltip = "This effect will provide a debuff to the tile and will affect everyone. Incompatible with the buff effect"),
	BUFF_PLAYER				UMETA(DisplayName = "Player Buff", Tooltip = "This effect will provide a buff to the tile (like increase dodge chance, heal/turn, etc). This will only affect a player unit. Incompatible with the player debuff effect"),
	DEBUFF_PLAYER			UMETA(DisplayName = "Player Debuff", Tooltip = "This effect will provide a debuff to the tile, and only affect a player unit. Incompatible with the player buff effect"),
	POWER_UP				UMETA(DisplayName = "Power up", Tooltip = "This effect will provide a power up that only a player unit can earn (increase weapon mastery, character experience, etc)"),

	GRIDTILEEFFECT_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGraphAStarResult : uint8
{
	SEARCH_FAIL,
	SEARCH_SUCCESS,
	UNREACHABLE_GOAL,
	INFINITE_LOOP,

	GRAPHASTARRESULT_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EGraphAStarHeuristic : uint8
{
	DEFAULT						UMETA(DisplayName = "Default", Tooltip = "Use a default heuristic (set to 1)"),
	MANHATTAN					UMETA(DisplayName = "Manhattan", Tooltip = "Use the manhattan distance for the heuristic"),

	GRAPHASTARHEURISTIC_COUNT	UMETA(Hidden)
};