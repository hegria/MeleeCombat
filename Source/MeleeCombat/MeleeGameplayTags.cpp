// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeGameplayTags.h"
#include "GameplayTagsManager.h"

FMeleeGameplayTags FMeleeGameplayTags::GameplayTags;

void FMeleeGameplayTags::InitializeNativeGameplayTags()
{
	
	GameplayTags.Attributes_Primary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxHealth"),
		FString("Maximum amount of Health obtainable")
	);

	GameplayTags.Attributes_Primary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.MaxStamina"),
		FString("Maximum amount of Mana obtainable")
	);
	GameplayTags.Attributes_Amt_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Amt.Health"),
		FString("Maximum amount of Mana obtainable")
	);
	GameplayTags.Attributes_Amt_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Amt.Stamina"),
		FString("Maximum amount of Mana obtainable")
	);
	/*
	 * Input Tags
	 */

	GameplayTags.InputTag_Block = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Block"),
		FString("")
	);
	GameplayTags.InputTag_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Dodge"),
		FString("")
	);
	GameplayTags.InputTag_HeavyAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.HeavyAttack"),
		FString("")
	);
	GameplayTags.InputTag_Interact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Interact"),
		FString("")
	);
	GameplayTags.InputTag_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Jump"),
		FString("")
	);
	GameplayTags.InputTag_LightAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LightAttack"),
		FString("")
	);
	GameplayTags.InputTag_Look = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Look"),
		FString("")
	);
	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Move"),
		FString("")
	);
	GameplayTags.InputTag_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Sprint"),
		FString("")
	);
	GameplayTags.InputTag_ToggleCombat = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ToggleCombat"),
		FString("")
	);
	GameplayTags.InputTag_ToggleLock = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ToggleLock"),
		FString("")
	);
	GameplayTags.InputTag_ToggleWalk = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.ToggleWalk"),
		FString("")
	);
	GameplayTags.InputTag_UseItem = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.UserItem"),
		FString("")
	);


	GameplayTags.Action_Attack_ChargedAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.ChargedAttack"),
		FString("")
	);
	GameplayTags.Action_Attack_FallingAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.FallingAttack"),
		FString("")
	);
	GameplayTags.Action_Attack_LightAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.LightAttack"),
		FString("")
	);
	GameplayTags.Action_Attack_HeavyAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.HeavyAttack"),
		FString("")
	);
	GameplayTags.Action_Attack_SprintAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.SprintAttack"),
		FString("")
	);
	GameplayTags.Action_Die = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.Die"),
		FString("")
	);
	GameplayTags.Action_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.Dodge"),
		FString("")
	);
	GameplayTags.Action_EnterBlocking = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.EnterBlocking"),
		FString("")
	);
	GameplayTags.Action_EnterCombat = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.EnterCombat"),
		FString("")
	);
	GameplayTags.Action_Executed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.Executed"),
		FString("")
	);
	GameplayTags.Action_ExitBlocking = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.ExitBlocking"),
		FString("")
	);
	GameplayTags.Action_ExitCombat = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.ExitCombat"),
		FString("")
	);
	GameplayTags.Action_GeneralAction = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.GeneralAction"),
		FString("")
	);
	GameplayTags.Action_UseItem = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Action.UserItem"),
		FString("")
	);


	GameplayTags.Player = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.Player"),
		FString("")
	);

	GameplayTags.State_Attacking = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.Attacking"),
		FString("")
	);
	GameplayTags.State_Blocking = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.Blocking"),
		FString("")
	);
	GameplayTags.State_Dead = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.Dead"),
		FString("")
	);
	GameplayTags.State_Disabled = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.Disabled"),
		FString("")
	);
	GameplayTags.State_Dodging = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.Dodging"),
		FString("")
	);
	GameplayTags.State_Executed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.Executed"),
		FString("")
	);
	GameplayTags.State_GeneralActionState = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Character.State.GeneralActionState"),
		FString("")
	);

}
