// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Character/CharacterStates.h"
#include "GameplayTagContainer.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MELEECOMBAT_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void RotateToActor(AActor* Excutor) = 0;
	virtual void MoveTo(FVector Start, FVector End) = 0;
	virtual void ConsumeItem() = 0;
	virtual void ContinueAttack() = 0;
	virtual void ResetCombat() = 0;
	virtual bool CanRecieveDamage() = 0;
	virtual void SetMoveable(bool CanMove) = 0;
	virtual FRotator GetDesireRotation() = 0;
	virtual ESpeedMode GetSpeedMode() = 0;
	virtual void PerformDeath(TArray<AActor*>&ActorToDestory, float& Duration ) =0;
	virtual bool PerformHitReaction(EDamageType DamageType, FVector HitLocation, float Damage) =0;
	virtual bool PerformUseItem(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, OUT float& ActionDuration) =0;
	virtual bool PerformAction(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, float& ActionDuration) =0;
	virtual bool PerformAttack(FGameplayTag AttackType, int MontageIndex, bool isRandomIndex, bool isCalledbyAI, float PlayRate, float& ActionDuration) =0;
	virtual void HandlePointDamage(const FHitResult& HitInfo,float Damage, EDamageType DamageType, FVector HitLocation) = 0;
};
