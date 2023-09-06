// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Class/FECharacterClassComponent.h"
#include "Character/Class/FEBaseClass.h"
#include "Character/FEBaseCharacter.h"


// Sets default values for this component's properties
UFECharacterClassComponent::UFECharacterClassComponent()
{
}

void UFECharacterClassComponent::SelectClass(const TSubclassOf<UFEBaseClass>& aChosenClass)
{
	CurrentClassInstance = NewObject<UFEBaseClass>(this, aChosenClass.Get());
	check(CurrentClassInstance);

	OnClassSelected.Broadcast(CurrentClassInstance);
}

UFEBaseClass* UFECharacterClassComponent::GetDefaultClass() const
{
	return DefaultClassInstance;
}

UFEBaseClass* UFECharacterClassComponent::GetCurrentClass() const
{
	return CurrentClassInstance;
}