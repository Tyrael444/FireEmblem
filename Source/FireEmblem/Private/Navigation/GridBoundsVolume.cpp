// Fill out your copyright notice in the Description page of Project Settings.


#include "Navigation/GridBoundsVolume.h"
#include "Components/BrushComponent.h"

AGridBoundsVolume::AGridBoundsVolume(const FObjectInitializer& anObjectInitializer)
{
	GetBrushComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	GetBrushComponent()->Mobility = EComponentMobility::Static;

	BrushColor = FColor(200, 200, 200, 255);

	bColored = true;

#if WITH_EDITORONLY_DATA
	bIsSpatiallyLoaded = false;
#endif
}