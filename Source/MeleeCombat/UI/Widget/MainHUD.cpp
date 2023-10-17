// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MainHUD.h"
#include "AbilitySystem/MeleeAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "UI/Widget/WidgetStatBar.h"
#include "Components/ProgressBar.h"

void UMainHUD::BindCallBacks()
{

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				WB_HealthStatBar->StatBar->SetPercent(data.NewValue / AttributeSet->GetMaxHealth());
			}
	);
	WB_HealthStatBar->StatBar->SetPercent(AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());
	UE_LOG(LogTemp, Log, TEXT("%f"), AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetStaminaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				WB_StaminaStatBar->StatBar->SetPercent(data.NewValue / AttributeSet->GetMaxStamina());
			}
	);
	UE_LOG(LogTemp, Log, TEXT("%f"), AttributeSet->GetStamina() / AttributeSet->GetMaxStamina());
	WB_StaminaStatBar->StatBar->SetPercent(AttributeSet->GetStamina() / AttributeSet->GetMaxStamina());
}
