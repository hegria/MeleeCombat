// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MeleeEnemy.generated.h"

/**
 * 
 */

class UWidgetComponent;
class UUserWidget;
class UEnemyHealthBar;

UCLASS()
class MELEECOMBAT_API AMeleeEnemy : public ABaseCharacter
{
	GENERATED_BODY()
public:	
	AMeleeEnemy();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> LockOnWidgetComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LockOnWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<class ATargetPoint*> TargetPoints;

	virtual void InitAbilityActorInfo() override;
	void OnTargeted(bool IsTargeted) override;
	bool bShowHeadHealthBar;
};
