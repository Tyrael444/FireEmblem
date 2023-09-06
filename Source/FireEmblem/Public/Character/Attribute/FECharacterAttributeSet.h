// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "FECharacterAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFECharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	/********
	* Replication methods
	********/

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_CurrentHealth(const FGameplayAttributeData& anOldCurrentHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& anOldMaxHealth);

	UFUNCTION()
	virtual void OnRep_CurrentStrength(const FGameplayAttributeData& anOldCurrentStrength);

	UFUNCTION()
	virtual void OnRep_MaxStrength(const FGameplayAttributeData& anOldMaxStrength);

	UFUNCTION()
	virtual void OnRep_CurrentMagic(const FGameplayAttributeData& anOldCurrentMagic);

	UFUNCTION()
	virtual void OnRep_MaxMagic(const FGameplayAttributeData& anOldMaxMagic);

	UFUNCTION()
	virtual void OnRep_CurrentDexterity(const FGameplayAttributeData& anOldCurrentDexterity);

	UFUNCTION()
	virtual void OnRep_MaxDexterity(const FGameplayAttributeData& anOldMaxDexterity);

	UFUNCTION()
	virtual void OnRep_CurrentSpeed(const FGameplayAttributeData& anOldCurrentSpeed);

	UFUNCTION()
	virtual void OnRep_MaxSpeed(const FGameplayAttributeData& anOldMaxSpeed);

	UFUNCTION()
	virtual void OnRep_CurrentLuck(const FGameplayAttributeData& anOldCurrentLuck);

	UFUNCTION()
	virtual void OnRep_MaxLuck(const FGameplayAttributeData& anOldMaxLuck);

	UFUNCTION()
	virtual void OnRep_CurrentDefense(const FGameplayAttributeData& anOldCurrentDefense);

	UFUNCTION()
	virtual void OnRep_MaxDefense(const FGameplayAttributeData& anOldMaxDefense);

	UFUNCTION()
	virtual void OnRep_CurrentResistance(const FGameplayAttributeData& anOldCurrentResistance);

	UFUNCTION()
	virtual void OnRep_MaxResistance(const FGameplayAttributeData& anOldMaxResistance);

	UFUNCTION()
	virtual void OnRep_MoveRange(const FGameplayAttributeData& anOldMoveRange);


public:

	/* Defines the health attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_CurrentHealth)
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentHealth)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxHealth)


	/* Defines the strength attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Strength", ReplicatedUsing = OnRep_CurrentStrength)
	FGameplayAttributeData CurrentStrength;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentStrength)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Strength", ReplicatedUsing = OnRep_MaxStrength)
	FGameplayAttributeData MaxStrength;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxStrength)


	/* Defines the magic attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magic", ReplicatedUsing = OnRep_CurrentMagic)
	FGameplayAttributeData CurrentMagic;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentMagic)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magic", ReplicatedUsing = OnRep_MaxMagic)
	FGameplayAttributeData MaxMagic;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxMagic)


	/* Defines the dexterity attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dexterity", ReplicatedUsing = OnRep_CurrentDexterity)
	FGameplayAttributeData CurrentDexterity;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentDexterity)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dexterity", ReplicatedUsing = OnRep_MaxDexterity)
	FGameplayAttributeData MaxDexterity;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxDexterity)


	/* Defines the speed attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_CurrentSpeed)
	FGameplayAttributeData CurrentSpeed;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentSpeed)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Speed", ReplicatedUsing = OnRep_MaxSpeed)
	FGameplayAttributeData MaxSpeed;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxSpeed)


	/* Defines the luck attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Luck", ReplicatedUsing = OnRep_CurrentLuck)
	FGameplayAttributeData CurrentLuck;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentLuck)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Luck", ReplicatedUsing = OnRep_MaxLuck)
	FGameplayAttributeData MaxLuck;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxLuck)


	/* Defines the defense attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_CurrentDefense)
	FGameplayAttributeData CurrentDefense;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentDefense)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Defense", ReplicatedUsing = OnRep_MaxDefense)
	FGameplayAttributeData MaxDefense;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxDefense)


	/* Defines the resistance attributes */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_CurrentResistance)
	FGameplayAttributeData CurrentResistance;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, CurrentResistance)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Resistance", ReplicatedUsing = OnRep_MaxResistance)
	FGameplayAttributeData MaxResistance;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MaxResistance)


	/* Defines the character movement range */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", ReplicatedUsing = OnRep_MoveRange)
	FGameplayAttributeData MoveRange;
	ATTRIBUTE_ACCESSORS(UFECharacterAttributeSet, MoveRange);
};