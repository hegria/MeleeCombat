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
class UMainHUD;
//class UAuraAbilitySystemComponent;

UCLASS()
class MELEECOMBAT_API AMeleePlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

public:
	void InitHUD();

protected:
	void Move(const struct FInputActionValue& value);
	void Look(const struct FInputActionValue& value);
	void LightAttackTriggered(const struct FInputActionInstance& instance);
	void LightAttackStarted(const struct FInputActionInstance& instance);

	void JumpTriggered();
	void JumpCompleted();
	void ToggleCombatCompleted();
	void InteractStarted();
	void DodgeStarted();
	void ToggleWalkStarted();
	void SprintTriggered();
	void SprintCompleted();
	void HeavyAttackCompleted();
	void ToggleLockStarted();
	void BlockStarted();
	void BlockCompleted();
	void UseItemStarted();


private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> MeleeContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LightClickAction;
public:
	void AbilityInputTagStarted(FGameplayTag InputTag);
	void AbilityInputTagCompleted(FGameplayTag InputTag);
	void AbilityInputTagTriggered(FGameplayTag InputTag);

	UPROPERTY()
	TObjectPtr<ABaseCharacter> PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMeleeInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UMainHUD> HUD;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainHUD> MainHUDClass;
	
};
