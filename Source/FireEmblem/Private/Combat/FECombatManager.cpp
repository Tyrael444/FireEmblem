// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/FECombatManager.h"

/*
	Damage Formulas:

	Physical damage		= Strength + [Weapon Might x Effective coefficient] + Support bonus
	Physical defense	= Defense + Support bonus + terrain effect
	Magical damage		= Magic + [Weapon Might x Effective coefficient] + Support bonus
	Magical defence		= Resistance + Barrier/Pure Water bonus + Support bonus + Terrain bonus
	DAMAGE				= [(Physical damage – enemy’s Physical defence) or (Magical damage – enemy’s Magical defence)] x Critical coefficient

	Support bonus will vary depending on the characters, can increase damage, defense, avoidance, etc
	Effective coefficient: 2 if weapon is effective against enemy, 1 if not.
	Critical coefficient: 3 if critical is successful, 1 if not.
*/

/*
	Avoidance/Accuracy Formulas:

	Accuracy		= Weapon Hit + (Skill x 2) + Luck + Biorhythm bonus + Support bonus
	Avoid			= (Attack Speed x 2) + Luck + Biorhythm bonus + Support bonus + Terrain bonus [lowest value is 0]
	Battle accuracy	= Accuracy – enemy’s Avoid [lowest value is 0, highest value is 100]
	Staff accuracy	= {30 + [(Magic – enemy’s Resistance) x 5] + Skill} – (Distance between units x 2)

	Biorhythm bonus: TBD (like a general mood for the character)
	Support bonus will vary depending on the characters, can increase damage, defense, avoidance, etc
*/

/*
	Crit Formulas:

	Critical rate			= Weapon Critical + (Skill / 2) + Support bonus + Critical bonus
	Dodge					= Luck + Support bonus
	Battle critical rate	= Critical rate – enemy’s Dodge
*/

/*
	XP Formulas:

	Power							= Level + Class bonus
	Battle Exp base					= (21 + [enemy’s Power – Power]) / 2 + Easy mode bonus
	Experience from doing no damage	= 1
	Experience from damaging enemy	= Battle Exp base x Skill coefficient
	Experience from defeating enemy	= (Battle Exp base + [enemy’s Power – Power] + Mode bonus + Boss bonus) x Skill coefficient

	Class bonus: Will depend on the class tier, the higher, the higher the bonus
	Easy mode bonus: X if Easy mode (TBD)
	Skill coefficient: 2 if character has the XP Increase skill (name TBD), 0.7 if character has XP lowered skill (name TBD), 1 if character has neither
	Mode bonus: X for Easy mode, Y for Normal mode, Z for Hard mode, XX for Maniac mode
	Boss bonus: X if enemy is a boss, Y if enemy is a boss in Easy mode
*/

void UFECombatManager::InitiateCombat(const IFECombatAgent& anAttacker, const IFECombatAgent& aDefender)
{
}

void UFECombatManager::ProcessCombat(const IFECombatAgent& anAttacker, const IFECombatAgent& aDefender)
{
}