// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Combat/FECombatAgent.h"
#include "Combat/FECombatData.h"
#include "Dialogue/FEDialogueAgent.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "Turn/FETurnAgent.h"
#include "FEBaseCharacter.generated.h"

class UFEAbilitySystemComponent;
class UFEBaseClass;
class UFEBaseItem;
class UFEBaseGameplayAbility;
class UFECharacterAttributeSet;	
class UFECharacterClassComponent;	
class UFEGrowthDataAsset;
class UFEInventoryComponent;
class UFESupportComponent;

class FEStoryElement;				// defines the character story background, tags, etc
class FEDialogueSystem;				// link to the dialogue system

UCLASS(BlueprintType, meta=(Tooltip = "Base class for every character of the Fire Emblem Project."))
class FIREEMBLEM_API AFEBaseCharacter : public AActor, public IFECombatAgent, public IGenericTeamAgentInterface, public IAbilitySystemInterface, 
										public IFEDialogueAgent, public IFETurnAgent
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AFEBaseCharacter();

	const TObjectPtr<UFEGrowthDataAsset> GetCharacterGrowthData() const;


	/************
	* Supers overrides
	************/

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	const UFECharacterClassComponent* GetCharacterClassComponent() const;


	/************
	* Team methods
	************/

	/* Get the character current team */
	EFETeam GetCharacterTeam() const;

	/* Modify this character current team */
	UFUNCTION(BlueprintCallable)
	void ChangeCharacterTeam(EFETeam aNewTeam);


protected:

	/* Init the components, setup callbacks, etc */
	virtual void InitComponents();

	/* Will setup the character growth rates depending a class and the character base one */
	virtual void SetupCharacterGrowthData(const TObjectPtr<UFEGrowthDataAsset> aGrowthDataAsset);

	/* Will do the actual levelup, increasing character stats depending on its growth rate */
	virtual void LevelUp_Internal();

	/* Will calculate the character combat data depending on its stats and current weapon (if any) */
	virtual void CalculateCombatData();


	/************
	* Combat Agent overrides
	************/

	virtual const UFEInventoryComponent* GetAgentInventory_Implementation() const override;

	virtual const UFEExperienceComponent* GetAgentExperienceComponent_Implementation() const override;

	virtual EFETeam GetAgentTeam_Implementation() const override;

	virtual FFECombatData GetAgentCombatData_Implementation() const override;


	/************
	* Turn Agent overrides
	************/

	virtual void OnTurnStarted_Implementation() const override;

	virtual void OnTurnEnded_Implementation() const override;


	/************
	* Delegate methods
	************/

	/* Callback when selecting a class
	* Will setup the new growth rate
	* Other stuff ?
	*/
	UFUNCTION()
	virtual void OnClassSelected(const UFEBaseClass* aSelectedClass);

	/* Callback when increasing the combat level */
	UFUNCTION()
	virtual void OnCombatLevelUp();

	/* Callback when increasing a weapon mastery */
	UFUNCTION()
	virtual void OnWeaponMasteryLevelUp(EFEWeaponType aWeaponType, EFEWeaponRank aNewRank);

	/* Callback of when an item is equipped */
	UFUNCTION()
	virtual void OnItemEquipped(const UFEBaseItem* anEquippedItem, bool bIsEquipped);


protected:

	/************
	* Abilities
	************/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UFEBaseGameplayAbility>> CharacterDefaultAbilities;


	/************
	* Attributes / Data asset
	************/

	/* Character current attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UFECharacterAttributeSet> CharacterAttribute;

	/* Character default growth attributes. This will be added to the class one */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UFEGrowthDataAsset> BaseGrowthData;

	/* Defines the character growth rate, which will be used during a levelup */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UFEGrowthDataAsset> GrowthData;

	/* Character combat attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FFECombatData CombatData;


	/************
	* Components
	************/

	/* Character inventory component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFEInventoryComponent> InventoryComponent;

	/* Character class component, which manage all the class stuff */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFECharacterClassComponent> ClassComponent;

	/* Character ability system component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFEAbilitySystemComponent> AbilitySystemComponent;

	/* Character experience component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFEExperienceComponent> ExperienceComponent;

	/* Character support component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UFESupportComponent> SupportComponent;


	/************
	* Team
	************/

	/* Defines the character current team. Could be modified at runtime */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Team")
	EFETeam CharacterTeam;
};