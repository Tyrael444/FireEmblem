// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/FEGameMode.h"
#include "../FireEmblemPlayerController.h"
#include "../FireEmblemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFEGameMode::AFEGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFireEmblemPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}