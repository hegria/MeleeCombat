// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/MeleeUserWidget.h"
#include "EnemyHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UEnemyHealthBar : public UMeleeUserWidget
{
	GENERATED_BODY()
	virtual void BindCallBacks() override;
public:
	UPROPERTY(BlueprintReadOnly,meta = (BindWidget))
	class UProgressBar* HealthBar;
};
