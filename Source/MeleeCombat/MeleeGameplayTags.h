// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

struct FMeleeGameplayTags
{
public:
	static const FMeleeGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

public:
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	FGameplayTag Action_Attack_ChargedAttack;
	FGameplayTag Action_Attack_FallingAttack;
	FGameplayTag Action_Attack_LightAttack;
	FGameplayTag Action_Attack_HeavyAttack;
	FGameplayTag Action_Die;
	FGameplayTag Action_Dodge;
	FGameplayTag Action_EnterBlocking;
	FGameplayTag Action_EnterCombat;
	FGameplayTag Action_Executed;
	FGameplayTag Action_ExitBlocking;
	FGameplayTag Action_ExitCombat;
	FGameplayTag Action_GeneralAction;
	FGameplayTag Action_UserItem;

	FGameplayTag Player;

	FGameplayTag State_Attacking;
	FGameplayTag State_Blocking;
	FGameplayTag State_Dead;
	FGameplayTag State_Disabled;
	FGameplayTag State_Dodging;
	FGameplayTag State_Executed;
	FGameplayTag State_GeneralActionState;




private:
	static FMeleeGameplayTags GameplayTags;
};