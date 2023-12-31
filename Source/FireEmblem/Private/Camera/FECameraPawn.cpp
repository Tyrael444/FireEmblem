// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/FECameraPawn.h"

#include "Camera/CameraComponent.h"
#include "Camera/FECameraData.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameInstance/FEGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/GridManager.h"
#include "Navigation/Pathfinding/GenericPathfinder.h"

AFECameraPawn::AFECameraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Top Down Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
}

void AFECameraPawn::BeginPlay()
{
	Super::BeginPlay();

	InitComponents();
}

void AFECameraPawn::InitComponents()
{
	check(CameraData);

	SpringArmComponent->TargetArmLength = CameraData->DefaultSpringArmLength;
	SpringArmComponent->SetRelativeRotation(CameraData->DefaultSpringArmRotation);

	TargetRotation = SpringArmComponent->GetRelativeRotation();
	TargetZoom = SpringArmComponent->TargetArmLength;
	TargetLocation = SpringArmComponent->GetRelativeLocation();
}

void AFECameraPawn::PostEditChangeProperty(FPropertyChangedEvent& anEvent)
{
	Super::PostEditChangeProperty(anEvent);

	FName propertyName = (anEvent.Property != NULL) ? anEvent.Property->GetFName() : NAME_None;
	if (propertyName == GET_MEMBER_NAME_CHECKED(AFECameraPawn, CameraData))
	{
		if (CameraData)
			InitComponents();
	}
}

bool AFECameraPawn::CanZoom(float aValue)
{
	// Try to zoom in if value < 0
	if (aValue < 0)
	{
		TargetZoomSpeed = CameraData->ZoomInSpeed;
		if ((SpringArmComponent->TargetArmLength - CameraData->ZoomStep) < CameraData->MaxZoom)
			return false;
	}
	else
	{
		TargetZoomSpeed = CameraData->ZoomOutSpeed;
		if ((SpringArmComponent->TargetArmLength + CameraData->ZoomStep) > CameraData->MinZoom)
			return false;
	}

	return true;
}

void AFECameraPawn::UpdateHoveredTile()
{
	FHitResult hit;

	FVector start = SpringArmComponent->GetComponentLocation();
	FVector end = start + (GetActorForwardVector() * 2500);

	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Camera))
	{
		AGridManager::GetInstance()->UpdateHoveredTile(hit.Location);
	}
}

void AFECameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator newCameraRotation = FMath::RInterpTo(SpringArmComponent->GetRelativeRotation(), TargetRotation, DeltaTime, CameraData->RotationSpeed);
	SpringArmComponent->SetRelativeRotation(newCameraRotation);

	SpringArmComponent->TargetArmLength = FMath::Lerp(SpringArmComponent->TargetArmLength, TargetZoom, DeltaTime * TargetZoomSpeed);

	SpringArmComponent->SetRelativeLocation(FMath::VInterpTo(SpringArmComponent->GetRelativeLocation(), TargetLocation, DeltaTime, CameraData->MovementSpeed));

	UpdateHoveredTile();
}

void AFECameraPawn::MoveCamera(const FInputActionInstance& anInstance)
{
	FVector2D inputValue = anInstance.GetValue().Get<FVector2D>();
	FVector direction = (FVector::ForwardVector * inputValue.X + FVector::RightVector * inputValue.Y).GetSafeNormal();
	TargetLocation = SpringArmComponent->GetRelativeLocation() + direction * CameraData->MovementSpeed;
}

void AFECameraPawn::RotateCamera(const FInputActionInstance& anInstance)
{
	float yawRad = FMath::DegreesToRadians(anInstance.GetValue().Get<float>() * CameraData->RotationStep);

	TargetRotation = FRotator(FQuat(FVector::UpVector, yawRad) * FQuat(TargetRotation));
}

void AFECameraPawn::CameraZoom(const FInputActionInstance& anInstance)
{
	float value = anInstance.GetValue().Get<float>();
	if (!CanZoom(value))
		return;

	float distanceToMinZoom = FMath::Abs(TargetZoom - CameraData->MinZoom);
	float distanceToMaxZoom = FMath::Abs(TargetZoom - CameraData->MaxZoom);

	float interpSpeed = 0.5f;

	TargetZoom = SpringArmComponent->TargetArmLength + CameraData->ZoomStep * value;

	TargetZoomSpeed = FMath::Lerp(TargetZoomSpeed, (value < 0) ? CameraData->ZoomInSpeed : CameraData->ZoomOutSpeed, FMath::Min(distanceToMinZoom, distanceToMaxZoom) * interpSpeed);
}