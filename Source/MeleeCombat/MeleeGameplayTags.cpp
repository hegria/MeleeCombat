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

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
	);

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
	);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
	);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
	);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
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
