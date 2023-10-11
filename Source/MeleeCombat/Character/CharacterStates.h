#pragma once

UENUM(BlueprintType)
enum class ECombatType : uint8
{
	ECT_None UMETA(DisplayName = "None"),
	ECT_LightSword UMETA(DisplayName = "LightSword"),
	ECT_GreatSword UMETA(DisplayName = "GreatSword"),
	ECT_TwinSword UMETA(DisplayName = "TwinSword"),
};

UENUM(BlueprintType)
enum class ECollisionPart : uint8
{
	ECP_MainWeapon UMETA(DisplayName = "MainWeapon"),
};

UENUM(BlueprintType)
enum class ERotationMode : uint8
{
	ERM_OrientToCamera,
	ERM_OrientToMovement
};


UENUM(BlueprintType)
enum class ESpeedMode : uint8
{
	ESM_Walking,
	ESM_Jogging,
	ESM_Sprinting,
};

UENUM(BlueprintType)
enum class EDamegeType : uint8
{
	EDT_None,
	ESM_MeleeDamage,
	ESM_KnockdownDamage,
};