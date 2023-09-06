// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FECharacterClassComponent.generated.h"

class UFEBaseClass;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFEOnClassSelected, const UFEBaseClass*, aChosenClass);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIREEMBLEM_API UFECharacterClassComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UFECharacterClassComponent();

	/* Called when selecting a class */
	void SelectClass(const TSubclassOf<UFEBaseClass>& aChosenClass);

	
	/************
	* Helpers
	************/

	/* Access the character default class */
	UFUNCTION(BlueprintCallable)
	UFEBaseClass* GetDefaultClass() const;

	/* Access the character current class, might be the same as the default one */
	UFUNCTION(BlueprintCallable)
	UFEBaseClass* GetCurrentClass() const;


public:

	/************
	* Delegate
	************/

	UPROPERTY(BlueprintAssignable)
	FFEOnClassSelected OnClassSelected;


protected:

	/* Defines the default class for this component, and therefor the character */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Class")
	TSubclassOf<UFEBaseClass> DefaultClass;

	/* Instance of the default class */
	UPROPERTY(BlueprintReadOnly, Category = "Class")
	TObjectPtr<UFEBaseClass> DefaultClassInstance;

	/* Instance of the current class. Can be the same as the DefaultClassInstance */
	UPROPERTY(BlueprintReadOnly, Category = "Class")
	TObjectPtr<UFEBaseClass> CurrentClassInstance;
};