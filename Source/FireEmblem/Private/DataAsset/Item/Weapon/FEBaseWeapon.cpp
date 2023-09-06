// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Item/Weapon/FEBaseWeapon.h"

const int UFEBaseWeapon::GetMight() const
{
    return Might;
}

const int UFEBaseWeapon::GetHitChance() const
{
    return HitChance;
}

const int UFEBaseWeapon::GetCritRate() const
{
    return CritRate;
}

const int UFEBaseWeapon::GetWeight() const
{
    return Weight;
}

const EFEWeaponRank UFEBaseWeapon::GetWeaponRank() const
{
    return Rank;
}

const EFEWeaponType UFEBaseWeapon::GetWeaponType() const
{
    return Type;
}