// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Item/FEBaseItem.h"

const FName& UFEBaseItem::GetItemName() const
{
    return ItemName;
}

const int UFEBaseItem::GetGoldValue() const
{
    return GoldValue;
}

const UFEBaseGameplayAbility* UFEBaseItem::GetAbility() const
{
    return Cast<UFEBaseGameplayAbility>(Ability.Get());
}