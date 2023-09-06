// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/FEEnum.h"
#include "FEExperienceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFEOnCombatLevelUp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFEOnWeaponMasteryLevelUp, EFEWeaponType, aWeaponType, EFEWeaponRank, aNewRank);

USTRUCT(Blueprintable)
struct FFECombatExperience
{
	GENERATED_BODY()

public:

	/* Current combat level */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experience")
	int Level = 1;

	/* Current Combat XP */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experience")
	int Experience = 0;
};

USTRUCT(Blueprintable)
struct FFEWeaponMastery
{
	GENERATED_BODY()

public:

	/* Defines the weapon rank for this mastery */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experience")
	TEnumAsByte<EFEWeaponRank> Rank = EFEWeaponRank::RANK_COUNT;

	/* Defines the current experience for this mastery */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Experience")
	int Experience = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIREEMBLEM_API UFEExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UFEExperienceComponent();


	/************
	* Experience methods
	************/

	/* Add anExperienceValue to the Combat experience and level up if needed */
	UFUNCTION(BlueprintCallable)
	void AddCombatExperience(const int anExperienceValue);

	/* Add aMasteryValue to the Weapon mastery and increase it's level if needed */
	UFUNCTION(BlueprintCallable)
	void AddWeaponMastery(const int aMasteryValue, const EFEWeaponType aWeaponType);

	/* Check if the combat level can be increased */
	UFUNCTION(BlueprintCallable)
	bool CanGainCombatExperience() const;

	/* Check if this weapon type can be increased */
	UFUNCTION(BlueprintCallable)
	bool CanGainWeaponMastery(const EFEWeaponType aWeaponType) const;

	/* Increase the combat level for this component */
	UFUNCTION(BlueprintCallable)
	void CombatLevelUp();

	/* Increase the weapon mastery for a specific weapon type */
	UFUNCTION(BlueprintCallable)
	void WeaponMasteryLevelUp(const EFEWeaponType aWeaponType);

	/* Resets the component XP and Level to the given value.
	* By default, it will be level 1 and XP 0
	*/
	UFUNCTION(BlueprintCallable)
	void ResetCombatExperience(int aDefaultCombatLevel = 1, int aDefaultCombatXP = 0);


	/********
	* Class methods
	********/

	/* Called when selecting a class. This will reset the level to 1 and XP to 0 */
	UFUNCTION(BlueprintCallable)
	void OnClassSelected();


public:


	/************
	* Delegates
	************/

	/* Event which will be broadcast when increasing the combat level */
	UPROPERTY(BlueprintAssignable)
	FFEOnCombatLevelUp OnCombatLevelUp;

	/* Event which will be broadcast when increasing a weapon mastery level */
	UPROPERTY(BlueprintAssignable)
	FFEOnWeaponMasteryLevelUp OnWeaponMasteryLevelUp;


protected:

	/* Component current combat experience */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat Experience")
	FFECombatExperience CombatExperience;

	/* Component current weapon mastery for each weapon type */
	UPROPERTY(VisibleAnywhere, BLueprintReadOnly, Category = "Weapon Mastery")
	TMap<TEnumAsByte<EFEWeaponType>, FFEWeaponMastery> WeaponMastery;
};