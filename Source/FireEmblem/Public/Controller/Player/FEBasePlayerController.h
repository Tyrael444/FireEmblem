// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "FEBasePlayerController.generated.h"

class AFECameraPawn;
class AGridNavMesh;
class UFECameraComponent;
class UInputMappingContext;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FFEMappingContext
{
	GENERATED_BODY()

public:

	/* Defines the tag associated with a mapping context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MappingTag;

	/* Context link to a tag */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> MappingContext;

	/* Defines the priority for a context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0"))
	int32 MappingPriority = 0;
};


/**
 * 
 */
UCLASS()
class FIREEMBLEM_API AFEBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AFEBasePlayerController();

	TObjectPtr<AFECameraPawn> GetCameraPawn() const;

	/********
	* Super overrides
	********/

	virtual void BeginPlay() override;

	/* Setup the input component */
	virtual void SetupInputComponent() override;


	/********
	* Camera methods
	********/

	/* Use to move the camera depending on it's actual position while making sure it's clamped to the grid bounds */
	void MoveCamera(const FInputActionInstance& anInstance);

	/* Handle the camera rotation */
	void RotateCamera(const FInputActionInstance& anInstance);

	/* Handle the camera zoom */
	void CameraZoom(const FInputActionInstance& anInstance);


	/********
	* Context methods
	********/

	/* Try to find a context from the PossibleContext array, and return it if found */
	TObjectPtr<UInputMappingContext> GetContext(const FGameplayTag& aTag);


protected:

	/* Defines the possible mapping context for our player controller */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Context")
	TArray<FFEMappingContext> PossibleContext;

	/* Defines the tag which will be used to get our default mapping context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Context")
	FGameplayTag DefaultContextTag;

	/* Default mapping Context */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input|Context")
	TObjectPtr<UInputMappingContext> CurrentMappingContext;

	/* Input action to move the camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> MoveCameraAction;

	/* Input action to rotate the camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> RotateCameraAction;

	/* Input action to do a camera zoom */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
	TObjectPtr<UInputAction> CameraZoomAction;

	/* Pointer to the grid, in order to clamp the camera to the grid bounds */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
	TWeakObjectPtr<AGridNavMesh> Grid;
};