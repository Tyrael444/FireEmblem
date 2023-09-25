// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FEGameInstance.generated.h"

class AGridNavMesh;
class UFEExperienceManager;
class UFECombatManager;

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFEGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	/* Access to the experience manager */
	UFUNCTION(BlueprintCallable)
	const UFEExperienceManager* GetExperienceManager() const;

	/* Access to the combat manager */
	UFUNCTION(BlueprintCallable)
	const UFECombatManager* GetCombatManager() const;
	

protected:

	/* Pointer to the experience manager, as we want it to be globally accessible */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Experience")
	TObjectPtr<UFEExperienceManager> ExperienceManager;

	/* Pointer to the combat manager */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UFECombatManager> CombatManager;
};