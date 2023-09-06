// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat/FECombatData.h"
#include "Enums/FEEnum.h"
#include "UObject/Interface.h"
#include "FECombatAgent.generated.h"

class UFEExperienceComponent;
class UFEInventoryComponent;

// Define the interface without inheriting from UInterface
UINTERFACE(MinimalAPI, BlueprintType)
class UFECombatAgent : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interface for combat agents.
 */
class FIREEMBLEM_API IFECombatAgent
{
    GENERATED_BODY()

public:

    /* Access to the agent inventory. Can return nullptr (when attacking destructible object for instance) */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat Agent")
    const UFEInventoryComponent* GetAgentInventory() const;

    /* Access to the agent experience component. Can return nullptr (when attacking destructible object for instance) */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat Agent")
    const UFEExperienceComponent* GetAgentExperienceComponent() const;

    /* Access to the agent combat data. Can return an unint one (all values to 0) */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat Agent")
    FFECombatData GetAgentCombatData() const;

    /* Access to the agent team. Will be used for xp gain, UI, etc */
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat Agent")
    EFETeam GetAgentTeam() const;


protected:

    virtual const UFEInventoryComponent* GetAgentInventory_Implementation() const;

    virtual const UFEExperienceComponent* GetAgentExperienceComponent_Implementation() const;

    virtual FFECombatData GetAgentCombatData_Implementation() const;

    virtual EFETeam GetAgentTeam_Implementation() const;
};