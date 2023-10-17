// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/EnemyHealthBar.h"
#include "AbilitySystem/MeleeAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"


void UEnemyHealthBar::BindCallBacks()
{

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& data)
			{
				HealthBar->SetPercent(data.NewValue / AttributeSet->GetMaxHealth());
			}
	);
	HealthBar->SetPercent(AttributeSet->GetHealth() / AttributeSet->GetMaxHealth());
}
