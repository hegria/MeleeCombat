// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#define GET_MELEE_TAG FMeleeGameplayTags::Get()


struct FMeleeGameplayTags
{
public:
	static const FMeleeGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

public:
	
	FGameplayTag Attributes_Primary_MaxHealth;
	FGameplayTag Attributes_Primary_MaxStamina;
	FGameplayTag Attributes_Amt_Health;
	FGameplayTag Attributes_Amt_Stamina;

	FGameplayTag InputTag_Block;
	FGameplayTag InputTag_Dodge;
	FGameplayTag InputTag_HeavyAttack;
	FGameplayTag InputTag_Interact;
	FGameplayTag InputTag_Jump;
	FGameplayTag InputTag_LightAttack;
	FGameplayTag InputTag_Look;
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Sprint;
	FGameplayTag InputTag_ToggleCombat;
	FGameplayTag InputTag_ToggleLock;
	FGameplayTag InputTag_ToggleWalk;
	FGameplayTag InputTag_UseItem;

	FGameplayTag Action_Attack_ChargedAttack;
	FGameplayTag Action_Attack_FallingAttack;
	FGameplayTag Action_Attack_LightAttack;
	FGameplayTag Action_Attack_HeavyAttack;
	FGameplayTag Action_Attack_SprintAttack;
	FGameplayTag Action_Die;
	FGameplayTag Action_Dodge;
	FGameplayTag Action_EnterBlocking;
	FGameplayTag Action_EnterCombat;
	FGameplayTag Action_Executed;
	FGameplayTag Action_ExitBlocking;
	FGameplayTag Action_ExitCombat;
	FGameplayTag Action_GeneralAction;
	FGameplayTag Action_UseItem;

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