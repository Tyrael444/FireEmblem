// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/FEGameInstance.h"
#include "Kismet/GameplayStatics.h"

const UFEExperienceManager* UFEGameInstance::GetExperienceManager() const
{
	return ExperienceManager;
}

const UFECombatManager* UFEGameInstance::GetCombatManager() const
{
	return CombatManager;
}