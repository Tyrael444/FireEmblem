// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Volume.h"
#include "GridBoundsVolume.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API AGridBoundsVolume : public AVolume
{
	GENERATED_BODY()

public:

	AGridBoundsVolume(const FObjectInitializer& anObjectInitializer);
};