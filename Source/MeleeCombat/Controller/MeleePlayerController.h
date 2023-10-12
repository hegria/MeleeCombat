// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "MeleePlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class UMeleeInputConfig;
class ABaseCharacter;
//class UAuraAbilitySystemComponent;

UCLASS()
class MELEECOMBAT_API AMeleePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	void Move(const struct FInputActionValue& value);
	void Look(const struct FInputActionValue& value);

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MeleeContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
public:
	void AbilityInputTagStarted(FGameplayTag InputTag);
	void AbilityInputTagCompleted(FGameplayTag InputTag);
	void AbilityInputTagTriggered(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<ABaseCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMeleeInputConfig> InputConfig;
	
};
