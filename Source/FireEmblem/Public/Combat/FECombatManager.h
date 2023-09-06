// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FECombatAgent.h"
#include "FECombatManager.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFECombatManager : public UObject
{
	GENERATED_BODY()

public:

	/* Initiate a combat between anAttacker and aDefender */
	void InitiateCombat(const IFECombatAgent& anAttacker, const IFECombatAgent& aDefender);


protected:

	/* Process a combat between anAttack and aDefender
	* Will calculate the damage, send them to both agents and calculate the XP gained by the player agent (could be the attacker or defender)
	*/
	void ProcessCombat(const IFECombatAgent& anAttacker, const IFECombatAgent& aDefender);
};