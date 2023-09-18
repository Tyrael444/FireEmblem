// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EFETeam : uint8
{
	PLAYER		UMETA(DisplayName = "Player Team"),
	ALLY		UMETA(DisplayName = "Ally Team"),
	NEUTRAL		UMETA(DisplayName = "Neutral Team"),
	ENEMY		UMETA(DisplayName = "Enemy Team"),

	TEAM_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFEWeaponRank : uint8
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
enum class EFEWeaponType : uint8
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
enum class EFEAbilityInputID : uint8
{
	NONE,
	CANCEL,
	CONFIRM,

	ABITILITYINPUTID_COUNT
};

UENUM(BlueprintType)
enum class EFEStatType : uint8
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

UENUM(BlueprintType)
enum class EFESupportLevel : uint8
{
	DEFAULT				UMETA(Tooltip = "Means that the support is unactive (doesn't provide any buffs)"),
	C					UMETA(Tooltip = "Lowest support level. Will provide the least amount of buffs"),
	B,
	A,
	S					UMETA(Tooltip = "Highest support level. Will provide the maximum amount of buffs"),

	SUPPORTLEVEL_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFEGridGenerationMethod : uint8
{
	BOUNDS						UMETA(DisplayName = "Bounds", Tooltip = "Generate the grid according to some bounds. The grid will be clamped to those bounds"),
	CENTER						UMETA(DisplayName = "Center", Tooltip = "Take a center position to generate the grid, without taking care of any possible bounds"),

	GRIDGENERATIONMETHOD_COUNT	UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EFECameraMode : uint8
{
	FREE				UMETA(DisplayName = "Free", Tooltip = "Free mode. Means the player have a complete control on it"),
	LOCK				UMETA(DisplayName = "Lock", Tooltip = "Lock mode. Means it will follow a character, without the player being able to have any control on the camera"),
	COMBAT				UMETA(DisplayName = "Combat", Tooltip = "Combat camera mode. The player doesn't have any control on the camera"),

	CAMERAMODE_COUNT	UMETA(Hidden)
};