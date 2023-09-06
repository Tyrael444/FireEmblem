// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Character/FEGrowthDataAsset.h"

void UFEGrowthDataAsset::SetupGrowthRate(const TObjectPtr<UFEGrowthDataAsset> aLeft, const TObjectPtr<UFEGrowthDataAsset> aRight)
{
    HealthGrowth = FMath::Clamp(aLeft->HealthGrowth + aRight->HealthGrowth, 0.f, 1.f);
    StrengthGrowth = FMath::Clamp(aLeft->StrengthGrowth + aRight->StrengthGrowth, 0.f, 1.f);
    MagicGrowth = FMath::Clamp(aLeft->MagicGrowth + aRight->MagicGrowth, 0.f, 1.f);
    DexterityGrowth = FMath::Clamp(aLeft->DexterityGrowth + aRight->DexterityGrowth, 0.f, 1.f);
    SpeedGrowth = FMath::Clamp(aLeft->SpeedGrowth + aRight->SpeedGrowth, 0.f, 1.f);
    LuckGrowth = FMath::Clamp(aLeft->LuckGrowth + aRight->LuckGrowth, 0.f, 1.f);
    DefenseGrowth = FMath::Clamp(aLeft->DefenseGrowth + aRight->DefenseGrowth, 0.f, 1.f);
    ResistanceGrowth = FMath::Clamp(aLeft->ResistanceGrowth + aRight->ResistanceGrowth, 0.f, 1.f);
}

const float UFEGrowthDataAsset::GetGrowth(EFEStatType aStatType) const
{
    float growth = 0.f;

    switch (aStatType)
    {
    case EFEStatType::HEALTH:
        growth = HealthGrowth;
        break;

    case EFEStatType::STRENGTH:
        growth = StrengthGrowth;
        break;

    case EFEStatType::MAGIC:
        growth = MagicGrowth;
        break;

    case EFEStatType::DEXTERITY:
        growth = DexterityGrowth;
        break;

    case EFEStatType::SPEED:
        growth = SpeedGrowth;
        break;

    case EFEStatType::LUCK:
        growth = LuckGrowth;
        break;

    case EFEStatType::DEFENSE:
        growth = DefenseGrowth;
        break;

    case EFEStatType::RESISTANCE:
        growth = ResistanceGrowth;
        break;

    default:
        break;
    }

    return growth;
}

const float UFEGrowthDataAsset::GetHealthGrowth() const
{
    return HealthGrowth;
}

const float UFEGrowthDataAsset::GetStrengthGrowth() const
{
    return StrengthGrowth;
}

const float UFEGrowthDataAsset::GetMagicGrowth() const
{
    return MagicGrowth;
}

const float UFEGrowthDataAsset::GetDexterityGrowth() const
{
    return DexterityGrowth;
}

const float UFEGrowthDataAsset::GetSpeedGrowth() const
{
    return SpeedGrowth;
}

const float UFEGrowthDataAsset::GetLuckGrowth() const
{
    return LuckGrowth;
}

const float UFEGrowthDataAsset::GetDefenseGrowth() const
{
    return DefenseGrowth;
}

const float UFEGrowthDataAsset::GetResistanceGrowth() const
{
    return ResistanceGrowth;
}