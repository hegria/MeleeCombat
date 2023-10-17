// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MeleeAttributeSet.h"
#include "MeleeGamePlayTags.h"
#include "GameplayEffectExtension.h"

UMeleeAttributeSet::UMeleeAttributeSet()
{
	const FMeleeGameplayTags& GameplayTags = FMeleeGameplayTags::Get();

	//GameplayTags.Attributes_Primary_Intelligence
	//GetIntelligence()

	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_MaxStamina, GetMaxStaminaAttribute);
}

void UMeleeAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());

	if (Attribute == GetStaminaAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
}

void UMeleeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
}
//
//void UMeleeAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
//{
//
//}
