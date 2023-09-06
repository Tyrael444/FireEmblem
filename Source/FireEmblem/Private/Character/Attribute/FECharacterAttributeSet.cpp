// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Attribute/FECharacterAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UFECharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentStrength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxStrength, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentMagic, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxMagic, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentDexterity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxDexterity, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxSpeed, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentLuck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxLuck, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentDefense, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxDefense, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, CurrentResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MaxResistance, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UFECharacterAttributeSet, MoveRange, COND_None, REPNOTIFY_Always);
}

void UFECharacterAttributeSet::OnRep_CurrentHealth(const FGameplayAttributeData& anOldCurrentHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentHealth, anOldCurrentHealth);
}

void UFECharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& anOldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxHealth, anOldMaxHealth);
}

void UFECharacterAttributeSet::OnRep_CurrentStrength(const FGameplayAttributeData& anOldCurrentStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentStrength, anOldCurrentStrength);
}

void UFECharacterAttributeSet::OnRep_MaxStrength(const FGameplayAttributeData& anOldMaxStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxStrength, anOldMaxStrength);
}

void UFECharacterAttributeSet::OnRep_CurrentMagic(const FGameplayAttributeData& anOldCurrentMagic)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentMagic, anOldCurrentMagic);
}

void UFECharacterAttributeSet::OnRep_MaxMagic(const FGameplayAttributeData& anOldMaxMagic)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxMagic, anOldMaxMagic);
}

void UFECharacterAttributeSet::OnRep_CurrentDexterity(const FGameplayAttributeData& anOldCurrentDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentDexterity, anOldCurrentDexterity);
}

void UFECharacterAttributeSet::OnRep_MaxDexterity(const FGameplayAttributeData& anOldMaxDexterity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxDexterity, anOldMaxDexterity);
}

void UFECharacterAttributeSet::OnRep_CurrentSpeed(const FGameplayAttributeData& anOldCurrentSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentSpeed, anOldCurrentSpeed);
}

void UFECharacterAttributeSet::OnRep_MaxSpeed(const FGameplayAttributeData& anOldMaxSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxSpeed, anOldMaxSpeed);
}

void UFECharacterAttributeSet::OnRep_CurrentLuck(const FGameplayAttributeData& anOldCurrentLuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentLuck, anOldCurrentLuck);
}

void UFECharacterAttributeSet::OnRep_MaxLuck(const FGameplayAttributeData& anOldMaxLuck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxLuck, anOldMaxLuck);
}

void UFECharacterAttributeSet::OnRep_CurrentDefense(const FGameplayAttributeData& anOldCurrentDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentDefense, anOldCurrentDefense);
}

void UFECharacterAttributeSet::OnRep_MaxDefense(const FGameplayAttributeData& anOldMaxDefense)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxDefense, anOldMaxDefense);
}

void UFECharacterAttributeSet::OnRep_CurrentResistance(const FGameplayAttributeData& anOldCurrentResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, CurrentResistance, anOldCurrentResistance);
}

void UFECharacterAttributeSet::OnRep_MaxResistance(const FGameplayAttributeData& anOldMaxResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MaxResistance, anOldMaxResistance);
}

void UFECharacterAttributeSet::OnRep_MoveRange(const FGameplayAttributeData& anOldMoveRange)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UFECharacterAttributeSet, MoveRange, anOldMoveRange);
}