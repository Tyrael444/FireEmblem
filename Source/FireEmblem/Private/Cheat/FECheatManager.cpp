// Fill out your copyright notice in the Description page of Project Settings.


#include "Cheat/FECheatManager.h"
#include "Navigation/Pathfinding/GenericPathfinder.h"
#include "Navigation/GridManager.h"

void UFECheatManager::Debug_ForceGetTilesInRange(int32 aRange)
{
	AGridManager::GetInstance()->Debug_ForceGetTilesInRange(aRange);
}