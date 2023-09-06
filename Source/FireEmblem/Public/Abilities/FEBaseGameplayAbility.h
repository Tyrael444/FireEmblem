// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Enums/FEEnum.h"
#include "FEBaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFEBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	/* Access to the ability input id */
	EFEAbilityInputID GetAbilityInputID() const;

protected:

	/* Define the ability input id, used to give the ability to the ASC */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TEnumAsByte<EFEAbilityInputID> AbilityInputID;
};