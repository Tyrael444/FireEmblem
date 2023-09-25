// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/Utility/GridBlueprintFunctionLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Navigation/GridManager.h"

bool UGridBlueprintFunctionLibrary::EnsureGirdManagerSingleton(const UObject* aWorldContext, bool bShouldDisplayError /*= true*/)
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(aWorldContext, AGridManager::StaticClass(), actors);

	if (actors.Num() != 1)
	{
		if (bShouldDisplayError)
		{
			UKismetSystemLibrary::PrintString(aWorldContext, "There is either none or more than one instance of AGridManager in the level. Please ensure that there is only one.",
				true, true, FLinearColor::Red, 20.f);
		}

		return false;
	}

	return true;
}