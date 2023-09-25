// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FEBaseItem.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFEBaseItem : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:


	/************
	* Helpers
	************/

	UFUNCTION(BlueprintCallable)
	const FName& GetItemName() const;

	UFUNCTION(BlueprintCallable)
	const int GetGoldValue() const;

	UFUNCTION(BlueprintCallable)
	const UFEBaseGameplayAbility* GetAbility() const;

protected:

	/* Defines the item name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Name")
	FName ItemName;

	/* Defines the item gold value, when purchasing it.
	* Will probably need another field when selling it, or some calculations to handle that
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Value")
	int GoldValue;

	/* Defines the item ability. Can be null if the item doesn't have a special ability. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	TSubclassOf<UFEBaseGameplayAbility> Ability;
};