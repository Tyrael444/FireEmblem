// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/Class/FEClassRequirement.h"
#include "FEClassDataAsset.generated.h"

class UFEGrowthDataAsset;
class UFEBaseGameplayAbility;
class UFEBaseClass;

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFEClassDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:


	/************
	* Helpers
	************/

	const TArray<FFEClassRequirement>& GetClassRequirements() const;

	const TObjectPtr<UFEGrowthDataAsset> GetGrowthData() const;

	const TArray<TSubclassOf<UFEBaseGameplayAbility>>& GetClassAbilities() const;

	const TArray<TSubclassOf<UFEBaseGameplayAbility>>& GetMasteredAbilities() const;

	const int GetClassTier() const;

	const TArray<TSubclassOf<UFEBaseClass>>& GetPossibleEvolutions() const;

	const int GetExperienceRequiredToMaster() const;

	const int GetClassMaxLevel() const;

protected:

	/* Class requirements, could be related to weapon mastery, level, etc */
	UPROPERTY(EditDefaultsOnly, Category = "Requirements")
	TArray<FFEClassRequirement> ClassRequirements;

	/* Growth attribute for this class. Will be added to the character growth attribute when changing to this class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Growth")
	TObjectPtr<UFEGrowthDataAsset> GrowthData;

	/* Defines the class abilities. Will be added to the character ability set when switching to this class */
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UFEBaseGameplayAbility>> ClassAbilities;

	/* Defines the class abilities which will be unlocked when a character masters this class */
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TArray<TSubclassOf<UFEBaseGameplayAbility>> MasteredAbilities;

	/* Defines the class tier. The higher the better are the abilities, growth, etc */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tier", meta = (UIMin = "1"))
	int ClassTier;

	/* Defines the class possible evolutions.
	* For instance: Mage -> Sorcerer -> etc
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Evolution")
	TArray<TSubclassOf<UFEBaseClass>> PossibleEvolutions;

	/* Required XP to master this class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience", meta = (ClampMin = "0"))
	int ExperienceRequiredToMaster;

	/* Max level for this class */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience", meta = (ClampMin = "0"))
	int MaxLevel;
};