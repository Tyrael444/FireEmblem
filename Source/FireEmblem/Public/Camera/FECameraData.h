// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FECameraData.generated.h"

/**
 * 
 */
UCLASS()
class FIREEMBLEM_API UFECameraData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	/* Defines the camera movement speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Movement")
	float MovementSpeed;

	/* Defines the speed for the camera rotation */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Rotation")
	float RotationSpeed;

	/* Defines the default rotation step for the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Rotation")
	float RotationStep;
	
	/* Defines the zoom step which will be performed when zooming in or out */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Zoom")
	float ZoomStep;

	/* Defines the max zoom for the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Zoom")
	float MaxZoom;

	/* Defines the min zoom for the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Zoom")
	float MinZoom;

	/* Defines the zoom in speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Zoom")
	float ZoomInSpeed;

	/* Defines the zoom out speed */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Zoom")
	float ZoomOutSpeed;

	/* Defines the default arm length for the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Spring Arm")
	float DefaultSpringArmLength;

	/* Defines the default arm length for the camera */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Default|Spring Arm")
	FRotator DefaultSpringArmRotation;
};