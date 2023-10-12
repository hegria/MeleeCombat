// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeGameplayTags.h"
#include "GameplayTagsManager.h"

FMeleeGameplayTags FMeleeGameplayTags::GameplayTags;

void FMeleeGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage")
	);

	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage")
	);

	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases Armor and Armor Penetration")
	);

	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases Health")
	);

	/*
	 * Secondary Attributes
	 */

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves Block Chance")
	);

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Ignores Percentage of enemy Armor, increases Critical Hit Chance")
	);

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Chance to cut incoming damage in half")
	);

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Chance to double damage plus critical hit bonus")
	);

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Bonus damage added when a critical hit is scored")
	);

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Reduces Critical Hit Chance of attacking enemies")
	);

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Amount of Health regenerated every 1 second")
	);

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Amount of Mana regenerated every 1 second")
	);

	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Maximum amount of Health obtainable")
	);

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
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
	GameplayTags.InputTag_UserItem = UGameplayTagsManager::Get().AddNativeGameplayTag(
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
	GameplayTags.Action_UserItem = UGameplayTagsManager::Get().AddNativeGameplayTag(
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
