// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FETurnAgent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFETurnAgent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIREEMBLEM_API IFETurnAgent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Turn Agent")
	void OnTurnStarted() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Turn Agent")
	void OnTurnEnded() const;

protected:

	virtual void OnTurnStarted_Implementation() const;

	virtual void OnTurnEnded_Implementation() const;
};