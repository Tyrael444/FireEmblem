// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FECombatData.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct FIREEMBLEM_API FFECombatData
{
	GENERATED_BODY()

public:

	/* Init those combat data by setting them all to 0 */
	void InitCombatData();

	/* Update the combat data to the given values */
	void UpdateCombatData(int anAttackSpeed, int anAccuracy, int anAvoidance, int aCritRate, int aCritAvoidance);


public:

	/* Defines the character attack speed, which will be used to know if he can hit twice during an attack */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Speed")
	int AttackSpeed = 0;

	/* Defines the chances for a character to strike an attack */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Accuracy")
	int Accuracy = 0;

	/* Defines the character chances to avoid an attack */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Avoidance")
	int Avoidance = 0;

	/* Defines the character crit rate */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Critical")
	int CritRate = 0;

	/* Defines the chances a character does have to avoid a critical hit */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Critical")
	int CritAvoidance = 0;
};