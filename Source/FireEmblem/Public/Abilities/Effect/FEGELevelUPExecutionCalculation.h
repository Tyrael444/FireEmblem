// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/FEEnum.h"
#include "GameplayEffectExecutionCalculation.h"
#include "FEGELevelUPExecutionCalculation.generated.h"

class AFEBaseCharacter;

struct FEStatWrapper
{
public:

	FEStatWrapper(EFEStatType aStatType);

	FProperty* Property;

	FGameplayEffectAttributeCaptureDefinition CurrentDef;
	FGameplayEffectAttributeCaptureDefinition MaxDef;

	EFEStatType StatType;
};

/**
 *
 */
UCLASS()
class FIREEMBLEM_API UFEGELevelUPExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UFEGELevelUPExecutionCalculation();

	/* Execution calculation function. Will be used to check for every stat if they are capped and if they will increase or not */
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


protected:

	/* Try to increase a given attribute using a wrapper for easier tests */
	bool TryIncreaseAttribute(const FEStatWrapper& aWrapper, const FGameplayEffectCustomExecutionParameters& someExecutionParams, const FAggregatorEvaluateParameters& someEvaluationParameters, const AFEBaseCharacter* aSourceCharacter) const;
};