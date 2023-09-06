// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Item/FEBaseItem.h"
#include "Enums/FEEnum.h"
#include "FEBaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFEBaseWeapon : public UFEBaseItem
{
	GENERATED_BODY()

public:


	/************
	* Helpers
	************/

	UFUNCTION(BlueprintCallable)
	const int GetMight() const;

	UFUNCTION(BlueprintCallable)
	const int GetHitChance() const;

	UFUNCTION(BlueprintCallable)
	const int GetCritRate() const;

	UFUNCTION(BlueprintCallable)
	const int GetWeight() const;

	UFUNCTION(BlueprintCallable)
	const EFEWeaponRank GetWeaponRank() const;

	UFUNCTION(BlueprintCallable)
	const EFEWeaponType GetWeaponType() const;

protected:

	/* Defines the weapon might, or "damage" */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Might", meta = (ClampMin = "0"))
	int Might;

	/* Defines the weapon default hit chance */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hit", meta = (ClampMin = "0"))
	int HitChance;

	/* Defines the weapon default crit chance */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crit", meta = (ClampMin = "0"))
	int CritRate;

	/* Defines the weapon weight, which will impact the wielder attack speed */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weight", meta = (ClampMin = "0"))
	int Weight;

	/* Defines the weapon type */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon type")
	TEnumAsByte<EFEWeaponType> Type;

	/* Weapon rank, the higher, the higher the mastery needs to be for a character to use this weapon */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Rank")
	TEnumAsByte<EFEWeaponRank> Rank;
};