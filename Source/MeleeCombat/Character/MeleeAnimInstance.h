// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/CharacterStates.h"
#include "MeleeAnimInstance.generated.h"

/**
 * 
 */
class ABaseCharacter;
class UCharacterMovementComponent;

UCLASS()
class MELEECOMBAT_API UMeleeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

public:
	FORCEINLINE void SetCombatType(ECombatType NewCombatType) { CombatType = NewCombatType; }
	FORCEINLINE void SetIsCombatEnabled(bool IsCombatEanabled) { bCombatEnabled = IsCombatEanabled; }
	FORCEINLINE void SetIsBlockingEnabled(bool IsBlockingEnabled) { bBlockingEnabled = IsBlockingEnabled; }

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<ABaseCharacter> Character;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	FVector Velocity;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bShouldMove;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bIsFalling;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	ECombatType CombatType;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bCombatEnabled;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool bBlockingEnabled;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float Direction;

};
