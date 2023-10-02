// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enums/FEEnum.h"
#include "InputAction.h"
#include "Navigation/Tile/BaseTile.h"
#include "FECameraPawn.generated.h"

class UCameraComponent;
class UDecalComponent;
class UFECameraData;
class USpringArmComponent;

UCLASS()
class FIREEMBLEM_API AFECameraPawn : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AFECameraPawn();


	/********
	* Camera methods
	********/

	void MoveCamera(const FInputActionInstance& anInstance);

	void RotateCamera(const FInputActionInstance& anInstance);

	void CameraZoom(const FInputActionInstance& anInstance);


protected:

	/********
	* Super overrides
	********/

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/* Init the actor components */
	void InitComponents();

#if WITH_EDITOR

	/* Post edit change property, to make sure that when we modify the camera component, we reinit everything related to it */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& anEvent) override;

#endif

	/* Test if we can zoom in the given direction (-1 for a zoom out and 1 for a zoom in) */
	bool CanZoom(float aValue);

	/* Update the currently hovered tile by the camera */
	void UpdateHoverTile();


protected:

	/* Camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	/* Spring arm component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	/* Camera data */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UFECameraData> CameraData;

	/* Current mode for the camera. By default, should be set to EFECameraMode::FREE */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera|Mode")
	EFECameraMode CurrentCameraMode = EFECameraMode::FREE;

	/* Target location of the camera */
	FVector TargetLocation;

	/* Targeted rotation of the camera */
	FRotator TargetRotation;

	/* Targeted zoom for the camera */
	float TargetZoom;

	/* Speed for the zoom */
	float TargetZoomSpeed;

	/* Currently hovered tile */
	FBaseTile HoveredTile;

	/* Decal component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Decal")
	TObjectPtr<UDecalComponent> DecalComponent;
};