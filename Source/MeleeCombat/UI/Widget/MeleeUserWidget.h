// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MeleeUserWidget.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UMeleeAttributeSet;

UCLASS()
class MELEECOMBAT_API UMeleeUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Init(UAbilitySystemComponent* ASC, UMeleeAttributeSet* AS);
	virtual void BindCallBacks() {};

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UMeleeAttributeSet> AttributeSet;
};
