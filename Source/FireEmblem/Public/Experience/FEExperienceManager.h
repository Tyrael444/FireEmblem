// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Enums/FEEnum.h"
#include "UObject/NoExportTypes.h"
#include "FEExperienceManager.generated.h"

class UFEExperienceComponent;

USTRUCT()
struct FFEWeaponRankExperience : public FTableRowBase
{
	GENERATED_BODY()

public:

	/* Rank of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EFEWeaponRank WeaponRank;

	/* Defines the experience required to master the given rank */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
	int ExperienceRequired;
};

/**
 * 
 */
UCLASS(Blueprintable)
class FIREEMBLEM_API UFEExperienceManager : public UObject
{
	GENERATED_BODY()

public:

	/* Get the required experience to increase the weapon mastery to a given level */
	UFUNCTION(BlueprintCallable)
	int GetExperienceRequired(EFEWeaponRank aWeaponRank) const;

	/* Get the required experience to increase the combat level */
	UFUNCTION(BlueprintCallable)
	int GetExperienceNeededToLevelUp() const;

protected:

	/* Defines the required experience to increase your combat level. Not sure if we should need a table or something to define it */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat Experience")
	int ExperienceNeededToLevelUp = 100;

	/* Defines the table that will be used for the various masteries for each weapon type and rank */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Mastery")
	TObjectPtr<UDataTable> WeaponMastery;
};