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
	ECP_OffHandWeapon,
	ECP_RightHand,
	ECP_LeftHand,
	ECP_RightFoot,
	ECP_LeftFoot
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
enum class EDamageType : uint8
{
	EDT_None,
	EDT_MeleeDamage,
	EDT_KnockdownDamage,
};

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	EHD_Front,
	EHD_Back,
	EHD_Left,
	EHD_Right,
};