// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Effect/FEGELevelUPExecutionCalculation.h"
#include "Abilities/FEAbilitySystemComponent.h"
#include "Character/FEBaseCharacter.h"
#include "Character/Attribute/FECharacterAttributeSet.h"
#include "DataAsset/Character/FEGrowthDataAsset.h"

/* Declare the attributes to capture and define how we want to capture them from the Source */
struct FEStatCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentStrength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxStrength);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentMagic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxMagic);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentDexterity);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxDexterity);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentSpeed);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxSpeed);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentLuck);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxLuck);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentDefense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxDefense);

	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxResistance);

	FEStatCapture()
	{
		/* Capture health attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentHealth, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxHealth, Source, false);

		/* Capture strength attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentStrength, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxStrength, Source, false);

		/* Capture magic attribute from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentMagic, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxMagic, Source, false);

		/* Capture dexterity attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentDexterity, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxDexterity, Source, false);

		/* Capture speed attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentSpeed, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxSpeed, Source, false);

		/* Capture luck attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentLuck, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxLuck, Source, false);

		/* Capture defense attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentDefense, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxDefense, Source, false);

		/* Capture resistance attributes from the source */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, CurrentResistance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UFECharacterAttributeSet, MaxResistance, Source, false);
	}
};

static const FEStatCapture& StatCapture()
{
	static FEStatCapture StatCaptured;
	return StatCaptured;
}


FEStatWrapper::FEStatWrapper(EFEStatType aStatType)
{
	StatType = aStatType;

	switch (aStatType)
	{
	case EFEStatType::HEALTH:
		Property = StatCapture().CurrentHealthProperty;
		CurrentDef = StatCapture().CurrentHealthDef;
		MaxDef = StatCapture().MaxHealthDef;
		break;

	case EFEStatType::STRENGTH:
		Property = StatCapture().CurrentStrengthProperty;
		CurrentDef = StatCapture().CurrentStrengthDef;
		MaxDef = StatCapture().MaxStrengthDef;
		break;

	case EFEStatType::MAGIC:
		Property = StatCapture().CurrentMagicProperty;
		CurrentDef = StatCapture().CurrentMagicDef;
		MaxDef = StatCapture().MaxMagicDef;
		break;

	case EFEStatType::DEXTERITY:
		Property = StatCapture().CurrentDexterityProperty;
		CurrentDef = StatCapture().CurrentDexterityDef;
		MaxDef = StatCapture().MaxDexterityDef;
		break;

	case EFEStatType::SPEED:
		Property = StatCapture().CurrentSpeedProperty;
		CurrentDef = StatCapture().CurrentSpeedDef;
		MaxDef = StatCapture().MaxSpeedDef;
		break;

	case EFEStatType::LUCK:
		Property = StatCapture().CurrentLuckProperty;
		CurrentDef = StatCapture().CurrentLuckDef;
		MaxDef = StatCapture().MaxLuckDef;
		break;

	case EFEStatType::DEFENSE:
		Property = StatCapture().CurrentDefenseProperty;
		CurrentDef = StatCapture().CurrentDefenseDef;
		MaxDef = StatCapture().MaxDefenseDef;
		break;

	case EFEStatType::RESISTANCE:
		Property = StatCapture().CurrentResistanceProperty;
		CurrentDef = StatCapture().CurrentResistanceDef;
		MaxDef = StatCapture().MaxResistanceDef;
		break;

	default:
		break;
	}
}

UFEGELevelUPExecutionCalculation::UFEGELevelUPExecutionCalculation()
{
	RelevantAttributesToCapture.Add(StatCapture().CurrentHealthDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxHealthDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentStrengthDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxStrengthDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentMagicDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxMagicDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentDexterityDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxDexterityDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentSpeedDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxSpeedDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentLuckDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxLuckDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentDefenseDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxDefenseDef);

	RelevantAttributesToCapture.Add(StatCapture().CurrentResistanceDef);
	RelevantAttributesToCapture.Add(StatCapture().MaxResistanceDef);
}

void UFEGELevelUPExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UFEAbilitySystemComponent* sourceASC = Cast<UFEAbilitySystemComponent>(ExecutionParams.GetSourceAbilitySystemComponent());

	AFEBaseCharacter* character = sourceASC ? Cast<AFEBaseCharacter>(sourceASC->GetAvatarActor()) : nullptr;

	const FGameplayEffectSpec& spec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters evaluationParameters;
	evaluationParameters.SourceTags = spec.CapturedSourceTags.GetAggregatedTags();

	for (int i = 0; i < (int)EFEStatType::STATTYPE_COUNT; ++i)
	{
		FEStatWrapper wrapper((EFEStatType)i);

		if (TryIncreaseAttribute(wrapper, ExecutionParams, evaluationParameters, character))
			OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(wrapper.Property, EGameplayModOp::Additive, 1));
	}
}

bool UFEGELevelUPExecutionCalculation::TryIncreaseAttribute(const FEStatWrapper& aWrapper, const FGameplayEffectCustomExecutionParameters& someExecutionParams, const FAggregatorEvaluateParameters& someEvaluationParameters, const AFEBaseCharacter* aSourceCharacter) const
{
	float currentValue = 0.f;
	someExecutionParams.AttemptCalculateCapturedAttributeMagnitude(aWrapper.CurrentDef, someEvaluationParameters, currentValue);
	currentValue = FMath::Max<float>(currentValue, 0.f);

	float maxValue = 0.f;
	someExecutionParams.AttemptCalculateCapturedAttributeMagnitude(aWrapper.MaxDef, someEvaluationParameters, maxValue);
	maxValue = FMath::Max<float>(maxValue, 0.f);

	if (currentValue < maxValue && FMath::RandRange(0, 1) <= aSourceCharacter->GetCharacterGrowthData()->GetGrowth(aWrapper.StatType))
		return true;

	return false;
}