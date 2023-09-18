// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FEBaseCharacter.h"
#include "Abilities/FEAbilitySystemComponent.h"
#include "Abilities/FEBaseGameplayAbility.h"
#include "Character/Attribute/FECharacterAttributeSet.h"
#include "Character/Class/FEBaseClass.h"
#include "Character/Class/FECharacterClassComponent.h"
#include "DataAsset/Character/FEGrowthDataAsset.h"
#include "DataAsset/Item/Weapon/FEBaseWeapon.h"
#include "Experience/FEExperienceComponent.h"
#include "Inventory/FEInventoryComponent.h"

// Sets default values
AFEBaseCharacter::AFEBaseCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InventoryComponent = CreateDefaultSubobject<UFEInventoryComponent>("Inventory");

	ClassComponent = CreateDefaultSubobject<UFECharacterClassComponent>("Character Class");

	ExperienceComponent = CreateDefaultSubobject<UFEExperienceComponent>("Experience Component");

	CharacterAttribute = CreateDefaultSubobject<UFECharacterAttributeSet>("Character Attribute");

	AbilitySystemComponent = CreateDefaultSubobject<UFEAbilitySystemComponent>("Ability Component");	
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	SupportComponent = CreateDefaultSubobject<UFESupportComponent>("Support Component");

	InitComponents();
}

const TObjectPtr<UFEGrowthDataAsset> AFEBaseCharacter::GetCharacterGrowthData() const
{
	return GrowthData;
}

void AFEBaseCharacter::InitComponents()
{
	InventoryComponent->OnItemEquipped.AddDynamic(this, &AFEBaseCharacter::OnItemEquipped);

	ClassComponent->OnClassSelected.AddDynamic(this, &AFEBaseCharacter::OnClassSelected);

	ExperienceComponent->OnCombatLevelUp.AddDynamic(this, &AFEBaseCharacter::OnCombatLevelUp);
	ExperienceComponent->OnWeaponMasteryLevelUp.AddDynamic(this, &AFEBaseCharacter::OnWeaponMasteryLevelUp);

	AbilitySystemComponent->AddAttributeSetSubobject<UFECharacterAttributeSet>(CharacterAttribute);

	for (auto& ability : CharacterDefaultAbilities)
	{
		// `1` below is the level of the ability, which could later be used to allow abilities to scale with player level
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(ability, 1, static_cast<int32>(ability.GetDefaultObject()->GetAbilityInputID()), this));
	}
}

UAbilitySystemComponent* AFEBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

const UFECharacterClassComponent* AFEBaseCharacter::GetCharacterClassComponent() const
{
	return ClassComponent;
}

const UFEInventoryComponent* AFEBaseCharacter::GetAgentInventory_Implementation() const
{
	return InventoryComponent;
}

const UFEExperienceComponent* AFEBaseCharacter::GetAgentExperienceComponent_Implementation() const
{
	return ExperienceComponent;
}

EFETeam AFEBaseCharacter::GetAgentTeam_Implementation() const
{
	return CharacterTeam;
}

FFECombatData AFEBaseCharacter::GetAgentCombatData_Implementation() const
{
	return CombatData;
}

void AFEBaseCharacter::OnTurnStarted_Implementation() const
{
}

void AFEBaseCharacter::OnTurnEnded_Implementation() const
{
}

EFETeam AFEBaseCharacter::GetCharacterTeam() const
{
	return CharacterTeam;
}

void AFEBaseCharacter::ChangeCharacterTeam(EFETeam aNewTeam)
{
	CharacterTeam = aNewTeam;

	// probably needs other logic here to correctly switch from a team to another
	//	TBD later
}

void AFEBaseCharacter::OnClassSelected(const UFEBaseClass* aSelectedClass)
{
	SetupCharacterGrowthData(aSelectedClass->GetClassGrowthRate());
}

void AFEBaseCharacter::OnCombatLevelUp()
{
	LevelUp_Internal();

	CalculateCombatData();
}

void AFEBaseCharacter::OnWeaponMasteryLevelUp(EFEWeaponType aWeaponType, EFEWeaponRank aNewRank)
{
	// might probably do mostly UI stuff
}

void AFEBaseCharacter::OnItemEquipped(const UFEBaseItem* anEquippedItem, bool bIsEquipped)
{
	CalculateCombatData();
}

void AFEBaseCharacter::SetupCharacterGrowthData(const TObjectPtr<UFEGrowthDataAsset> aGrowthDataAsset)
{
	GrowthData->SetupGrowthRate(BaseGrowthData, aGrowthDataAsset);
}

void AFEBaseCharacter::LevelUp_Internal()
{
	// call gameplay effect to increase stats?
}

void AFEBaseCharacter::CalculateCombatData()
{
	/*
	* Avoidance/Accuracy Formulas:
	* 	Accuracy		= Weapon Hit + (Skill x 2) + Luck + Biorhythm bonus + Support bonus
	* 	Avoid			= (Attack Speed x 2) + Luck + Biorhythm bonus + Support bonus + Terrain bonus [lowest value is 0]
	* 	Battle accuracy	= Accuracy – enemy’s Avoid [lowest value is 0, highest value is 100]
	* 	Staff accuracy	= {30 + [(Magic – enemy’s Resistance) x 5] + Skill} – (Distance between units x 2)
	* 
	* 	Biorhythm bonus: TBD (like a general mood for the character)
	* 	Support bonus will vary depending on the characters, can increase damage, defense, avoidance, etc
	*/

	/*
	* 	Crit Formulas:
	* 
	* 	Critical rate			= Weapon Critical + (Skill / 2) + Support bonus + Critical bonus
	* 	Dodge					= Luck + Support bonus
	* 	Battle critical rate	= Critical rate – enemy’s Dodge
	*/

	const UFEBaseWeapon* weapon = Cast<UFEBaseWeapon>(InventoryComponent->GetEquippedItem());

	if (!weapon)
	{
		CombatData.Accuracy = 0;
		CombatData.AttackSpeed = CharacterAttribute->GetCurrentSpeed();
		CombatData.CritRate = 0;
	}
	else
	{
		CombatData.Accuracy = weapon->GetHitChance() + (CharacterAttribute->GetCurrentDexterity() * 2) + CharacterAttribute->GetCurrentLuck();
		CombatData.AttackSpeed = CharacterAttribute->GetCurrentSpeed() - FMath::Max(weapon->GetWeight() - CharacterAttribute->GetCurrentStrength(), 0);
		CombatData.CritRate = weapon->GetCritRate() + (CharacterAttribute->GetCurrentDexterity() / 2);
	}

	CombatData.CritAvoidance = CharacterAttribute->GetCurrentLuck();
}