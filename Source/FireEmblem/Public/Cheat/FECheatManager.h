// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "FECheatManager.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFECheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:

	UFUNCTION(exec)
	void Debug_ForceGetTilesInRange(int32 aRange);
};