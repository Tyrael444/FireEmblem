// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/FECombatAgent.h"
#include "Combat/FECombatData.h"

const UFEInventoryComponent* IFECombatAgent::GetAgentInventory_Implementation() const
{
	return nullptr;
}

const UFEExperienceComponent* IFECombatAgent::GetAgentExperienceComponent_Implementation() const
{
	return nullptr;
}

EFETeam IFECombatAgent::GetAgentTeam_Implementation() const
{
	return EFETeam::TEAM_COUNT;
}

FFECombatData IFECombatAgent::GetAgentCombatData_Implementation() const
{
	return FFECombatData();
}