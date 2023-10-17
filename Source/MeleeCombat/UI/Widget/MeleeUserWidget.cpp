// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/MeleeUserWidget.h"

void UMeleeUserWidget::Init(UAbilitySystemComponent* ASC, UMeleeAttributeSet* AS)
{
	AbilitySystemComponent = ASC;
	AttributeSet = AS;
	BindCallBacks();
}
