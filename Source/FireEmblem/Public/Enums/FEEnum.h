// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum EFETeam : uint8
{
	PLAYER		UMETA(DisplayName = "Player Team"),
	ALLY		UMETA(DisplayName = "Ally Team"),
	NEUTRAL		UMETA(DisplayName = "Neutral Team"),
	ENEMY		UMETA(DisplayName = "Enemy Team"),

	TEAM_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum EFEWeaponRank : uint8
{
	E			UMETA(Tooltip = "Lowest level possible"),
	D,
	C,
	B,
	A,
	S			UMETA(Tooltip = "Highest level possible"),

	RANK_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum EFEWeaponType : uint8
{
	SWORD		UMETA(DisplayName = "Sword"),
	LANCE		UMETA(DisplayName = "Lance"),
	AXE			UMETA(DisplayName = "Axe"),
	BOW			UMETA(DisplayName = "Bow"),
	FIREMAGIC	UMETA(DisplayName = "Fire magic"),
	ICEMAGIC	UMETA(DisplayName = "Ice magic"),
	EARTHMAGIC	UMETA(DisplayName = "Earth magic"),
	WINDMAGIC	UMETA(DisplayName = "Wind magic"),
	LIGHTMAGIC	UMETA(DisplayName = "Light magic"),
	DARKMAGIC	UMETA(DisplayName = "Dark magic"),
	STAFF		UMETA(DisplayName = "Staff"),

	TYPE_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum EFEAbilityInputID : uint8
{
	NONE,
	CANCEL,
	CONFIRM,

	ABITILITYINPUTID_COUNT
};

UENUM(BlueprintType)
enum EFEStatType : uint8
{
	HEALTH			UMETA(DisplayName = "Health"),
	STRENGTH		UMETA(DisplayName = "Strength"),
	MAGIC			UMETA(DisplayName = "Magic"),
	DEXTERITY		UMETA(DisplayName = "Dexterity"),
	SPEED			UMETA(DisplayName = "Speed"),
	LUCK			UMETA(DisplayName = "Luck"),
	DEFENSE			UMETA(DisplayName = "Defense"),
	RESISTANCE		UMETA(DisplayName = "Resistance"),

	STATTYPE_COUNT	UMETA(Hidden)
};