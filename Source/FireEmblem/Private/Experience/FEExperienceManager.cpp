// Fill out your copyright notice in the Description page of Project Settings.


#include "Experience/FEExperienceManager.h"

int UFEExperienceManager::GetExperienceRequired(EFEWeaponRank aWeaponRank) const
{
	check(WeaponMastery);

	static const FString contextString(TEXT("UFEExperienceManager::GetExperienceRequired"));
	TArray<FFEWeaponRankExperience*> rows;
	WeaponMastery->GetAllRows<FFEWeaponRankExperience>(contextString, rows);

	for (auto row : rows)
	{
		if (row->WeaponRank == aWeaponRank)
			return row->ExperienceRequired;
	}

	return -1;
}

int UFEExperienceManager::GetExperienceNeededToLevelUp() const
{
	return ExperienceNeededToLevelUp;
}