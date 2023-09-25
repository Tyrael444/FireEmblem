// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GridBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UGridBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	/* Check if there is multiple instances of the grid manager in the level.
	* If there is, an error will be triggered if bShouldDisplayError is set to true.
	*/
	UFUNCTION(BlueprintPure, Category = "Grid|Utility")
	static bool EnsureGirdManagerSingleton(const UObject* aWorldContext, bool bShouldDisplayError = true);
};