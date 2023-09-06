// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/FECombatData.h"

void FFECombatData::InitCombatData()
{
	UpdateCombatData(0, 0, 0, 0, 0);
}

void FFECombatData::UpdateCombatData(int anAttackSpeed, int anAccuracy, int anAvoidance, int aCritRate, int aCritAvoidance)
{
	AttackSpeed = anAttackSpeed;
	Accuracy = anAccuracy;
	Avoidance = anAvoidance;
	CritRate = aCritRate;
	CritAvoidance = aCritAvoidance;
}