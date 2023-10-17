// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MeleeUserWidget.h"
#include "WidgetStatBar.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UWidgetStatBar : public UMeleeUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* StatBar;
};
