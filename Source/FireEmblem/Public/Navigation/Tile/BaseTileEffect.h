// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Navigation/Enum/GridEnums.h"
#include "BaseTileEffect.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UBaseTileEffect : public UDataAsset
{
	GENERATED_BODY()

public:

	/* Effect related to the tile */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EGridTileEffect TileEffect;
};