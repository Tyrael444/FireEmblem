// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/FEEnum.h"
#include "FEGrowthDataAsset.generated.h"

/**
 * Defines the various growth rates (aka chances to increase a stat) for each character stat
 */
UCLASS()
class FIREEMBLEM_API UFEGrowthDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/* Takes 2 growth rates and mix them up into a single one.
		Used when selecting a class for a character
	*/
	void SetupGrowthRate(const TObjectPtr<UFEGrowthDataAsset> aLeft, const TObjectPtr<UFEGrowthDataAsset> aRight);


	/************
	* Helpers
	************/

	UFUNCTION(BlueprintCallable)
	const float GetGrowth(EFEStatType aStatType) const;

	UFUNCTION(BlueprintCallable)
	const float GetHealthGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetStrengthGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetMagicGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetDexterityGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetSpeedGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetLuckGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetDefenseGrowth() const;

	UFUNCTION(BlueprintCallable)
	const float GetResistanceGrowth() const;

protected:

	/* Defines the health growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float HealthGrowth;

	/* Defines the strength growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Strength", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float StrengthGrowth;

	/* Defines the magic growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Magic", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MagicGrowth;

	/* Defines the dexterity growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dexterity", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DexterityGrowth;

	/* Defines the speed growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speed", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float SpeedGrowth;

	/* Defines the luck growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Luck", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float LuckGrowth;

	/* Defines the defense growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defense", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float DefenseGrowth;

	/* Defines the resistance growth */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Resistance", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float ResistanceGrowth;
};