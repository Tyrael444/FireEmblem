// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Class/FEBaseClass.h"
#include "DataAsset/Class/FEClassDataAsset.h"

const TObjectPtr<UFEClassDataAsset> UFEBaseClass::GetClassData() const
{
    return ClassData;
}

const TObjectPtr<UFEGrowthDataAsset> UFEBaseClass::GetClassGrowthRate() const
{
    return ClassData->GetGrowthData();
}

const TArray<TSubclassOf<UFEBaseGameplayAbility>>& UFEBaseClass::GetClassAbilities() const
{
    return ClassData->GetClassAbilities();
}

const TArray<TSubclassOf<UFEBaseGameplayAbility>>& UFEBaseClass::GetMasteredAbilities() const
{
    return ClassData->GetMasteredAbilities();
}

const int UFEBaseClass::GetClassTier() const
{
    return ClassData->GetClassTier();
}

const TArray<TSubclassOf<UFEBaseClass>>& UFEBaseClass::GetPossibleEvolutions() const
{
    return ClassData->GetPossibleEvolutions();
}

const TArray<FFEClassRequirement>& UFEBaseClass::GetClassRequirements() const
{
    return ClassData->GetClassRequirements();
}

const int UFEBaseClass::GetClassMaxLevel() const
{
    return ClassData->GetClassMaxLevel();
}

const int UFEBaseClass::GetExperienceRequiredToMaster() const
{
    return ClassData->GetExperienceRequiredToMaster();
}