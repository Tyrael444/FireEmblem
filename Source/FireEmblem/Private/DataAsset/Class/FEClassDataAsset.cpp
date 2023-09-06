// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Class/FEClassDataAsset.h"

const TArray<FFEClassRequirement>& UFEClassDataAsset::GetClassRequirements() const
{
	return ClassRequirements;
}

const TObjectPtr<UFEGrowthDataAsset> UFEClassDataAsset::GetGrowthData() const
{
	return GrowthData;
}

const TArray<TSubclassOf<UFEBaseGameplayAbility>>& UFEClassDataAsset::GetClassAbilities() const
{
	return ClassAbilities;
}

const TArray<TSubclassOf<UFEBaseGameplayAbility>>& UFEClassDataAsset::GetMasteredAbilities() const
{
	return MasteredAbilities;
}

const int UFEClassDataAsset::GetClassTier() const
{
	return ClassTier;
}

const TArray<TSubclassOf<UFEBaseClass>>& UFEClassDataAsset::GetPossibleEvolutions() const
{
	return PossibleEvolutions;
}

const int UFEClassDataAsset::GetExperienceRequiredToMaster() const
{
	return ExperienceRequiredToMaster;
}

const int UFEClassDataAsset::GetClassMaxLevel() const
{
	return MaxLevel;
}