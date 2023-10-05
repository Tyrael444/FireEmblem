// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/Player/FEBasePlayerController.h"
#include "Camera/FECameraPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AFEBasePlayerController::AFEBasePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bShowMouseCursor = false;
}

TObjectPtr<AFECameraPawn> AFEBasePlayerController::GetCameraPawn() const
{
	return Cast<AFECameraPawn>(GetPawn());
}

void AFEBasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = false;

	if (UEnhancedInputLocalPlayerSubsystem* inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (int i = 0; i < PossibleContext.Num(); ++i)
		{
			inputSystem->AddMappingContext(PossibleContext[i].MappingContext, PossibleContext[i].MappingPriority);
		}

		CurrentMappingContext = GetContext(DefaultContextTag);
	}
}

void AFEBasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();	
	
	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		enhancedInputComponent->BindAction(MoveCameraAction, ETriggerEvent::Triggered, this, &AFEBasePlayerController::MoveCamera);
		enhancedInputComponent->BindAction(RotateCameraAction, ETriggerEvent::Triggered, this, &AFEBasePlayerController::RotateCamera);
		enhancedInputComponent->BindAction(CameraZoomAction, ETriggerEvent::Triggered, this, &AFEBasePlayerController::CameraZoom);
	}
}

void AFEBasePlayerController::Tick(float aDeltaTime)
{
	Super::Tick(aDeltaTime);
}

void AFEBasePlayerController::MoveCamera(const FInputActionInstance& anInstance)
{
	GetCameraPawn()->MoveCamera(anInstance);
}

void AFEBasePlayerController::RotateCamera(const FInputActionInstance& anInstance)
{
	GetCameraPawn()->RotateCamera(anInstance);
}

void AFEBasePlayerController::CameraZoom(const FInputActionInstance& anInstance)
{
	GetCameraPawn()->CameraZoom(anInstance);
}

TObjectPtr<UInputMappingContext> AFEBasePlayerController::GetContext(const FGameplayTag& aTag)
{
	for (int i = 0; i < PossibleContext.Num(); ++i)
	{
		if (PossibleContext[i].MappingTag == aTag)
		{
			return PossibleContext[i].MappingContext;
		}
	}

	return nullptr;
}