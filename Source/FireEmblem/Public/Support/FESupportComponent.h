// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FESupportComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIREEMBLEM_API UFESupportComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UFESupportComponent();

protected:

	/* Contains all the support data for this component.
	* Can point to some "empty" data (with 0/default values)
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Support")
	TArray<int> SupportData;
};