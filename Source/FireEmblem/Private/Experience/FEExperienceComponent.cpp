// Fill out your copyright notice in the Description page of Project Settings.


#include "Experience/FEExperienceComponent.h"
#include "Character/FEBaseCharacter.h"
#include "Character/Class/FEBaseClass.h"
#include "Character/Class/FECharacterClassComponent.h"
#include "Experience/FEExperienceManager.h"
#include "GameInstance/FEGameInstance.h"

// Sets default values for this component's properties
UFEExperienceComponent::UFEExperienceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	/* sets the weapon mastery to default values */
	for (int i = 0; i < (int)EFEWeaponType::TYPE_COUNT; ++i)
	{
		WeaponMastery.Add(static_cast<EFEWeaponType>(i), FFEWeaponMastery());
	}
}

void UFEExperienceComponent::AddCombatExperience(const int anExperienceValue)
{
	CombatExperience.Experience += anExperienceValue;

	UFEGameInstance* gameInstance = Cast<UFEGameInstance>(GetOwner()->GetGameInstance());
	check(gameInstance);

	if (CombatExperience.Experience >= gameInstance->GetExperienceManager()->GetExperienceNeededToLevelUp())
	{
		CombatLevelUp();
	}
}

void UFEExperienceComponent::AddWeaponMastery(const int aMasteryValue, const EFEWeaponType aWeaponType)
{
	WeaponMastery[aWeaponType].Experience += aMasteryValue;

	UFEGameInstance* gameInstance = Cast<UFEGameInstance>(GetOwner()->GetGameInstance());
	check(gameInstance);

	if (WeaponMastery[aWeaponType].Experience >= gameInstance->GetExperienceManager()->GetExperienceRequired(WeaponMastery[aWeaponType].Rank))
	{
		WeaponMasteryLevelUp(aWeaponType);
	}
}

bool UFEExperienceComponent::CanGainCombatExperience() const
{
	AFEBaseCharacter* ownerCharacter = Cast<AFEBaseCharacter>(GetOwner());
	check(ownerCharacter);
	
	const UFECharacterClassComponent* classComp = ownerCharacter->GetCharacterClassComponent();
	check(classComp);

	UFEBaseClass* currentClass = classComp->GetCurrentClass();
	check(currentClass);

	/* ensure that the current level is lowered than the max one for our current class */
	if (currentClass->GetClassMaxLevel() > CombatExperience.Level)
		return true;

	return false;
}

bool UFEExperienceComponent::CanGainWeaponMastery(const EFEWeaponType aWeaponType) const
{
	// hardcoded for now, will see if we change it later
	return WeaponMastery[aWeaponType].Rank != EFEWeaponRank::S;
}

void UFEExperienceComponent::CombatLevelUp()
{
	CombatExperience.Level += 1;

	AFEBaseCharacter* ownerCharacter = Cast<AFEBaseCharacter>(GetOwner());
	check(ownerCharacter);

	const UFECharacterClassComponent* classComp = ownerCharacter->GetCharacterClassComponent();
	check(classComp);

	UFEBaseClass* currentClass = classComp->GetCurrentClass();
	check(currentClass);

	/* resets the combat xp to 0 incase we reached the max level */
	if (currentClass->GetClassMaxLevel() == CombatExperience.Level)
		CombatExperience.Experience = 0;
	else
	{
		UFEGameInstance* gameInstance = Cast<UFEGameInstance>(GetOwner()->GetGameInstance());
		check(gameInstance);

		CombatExperience.Experience = FMath::Clamp(CombatExperience.Experience - gameInstance->GetExperienceManager()->GetExperienceNeededToLevelUp(), 0, CombatExperience.Experience);
	}

	OnCombatLevelUp.Broadcast();
}

void UFEExperienceComponent::WeaponMasteryLevelUp(const EFEWeaponType aWeaponType)
{
	// probably need to find a better way to increament it, will see later
	WeaponMastery[aWeaponType].Rank = static_cast<EFEWeaponRank>(WeaponMastery[aWeaponType].Rank.GetIntValue() + 1);

	OnWeaponMasteryLevelUp.Broadcast(aWeaponType, WeaponMastery[aWeaponType].Rank);
}

void UFEExperienceComponent::OnClassSelected()
{
	ResetCombatExperience();
}

void UFEExperienceComponent::ResetCombatExperience(int aDefaultCombatLevel /*= 1*/, int aDefaultCombatXP /*= 0*/)
{
	CombatExperience.Experience = aDefaultCombatXP;
	CombatExperience.Level = aDefaultCombatLevel;
}