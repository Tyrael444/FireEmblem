// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FEBaseClass.generated.h"

class UFEClassDataAsset;
class UFEGrowthDataAsset;
struct FFEClassRequirement;

/**
 * 
 */
UCLASS(Blueprintable)
class FIREEMBLEM_API UFEBaseClass : public UObject
{
	GENERATED_BODY()

public:


	/********
	* Helpers
	********/

	const TObjectPtr<UFEClassDataAsset> GetClassData() const;

	const TObjectPtr<UFEGrowthDataAsset> GetClassGrowthRate() const;

	const TArray<TSubclassOf<UFEBaseGameplayAbility>>& GetClassAbilities() const;

	const TArray<TSubclassOf<UFEBaseGameplayAbility>>& GetMasteredAbilities() const;

	const int GetClassTier() const;

	const TArray<TSubclassOf<UFEBaseClass>>& GetPossibleEvolutions() const;

	const TArray<FFEClassRequirement>& GetClassRequirements() const;

	const int GetClassMaxLevel() const;

	const int GetExperienceRequiredToMaster() const;

protected:

	/* Points to the class data (requirements, growth, etc) */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Class Data")
	TObjectPtr<UFEClassDataAsset> ClassData;

	/* Defines if the class is mastered by the character or not */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Class Data")
	bool IsMastered = false;
};