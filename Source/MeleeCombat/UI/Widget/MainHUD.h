// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MeleeUserWidget.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UMainHUD : public UMeleeUserWidget
{
	GENERATED_BODY()

	virtual void BindCallBacks() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetStatBar* WB_HealthStatBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetStatBar* WB_StaminaStatBar;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ItemAmountText;
	
};
