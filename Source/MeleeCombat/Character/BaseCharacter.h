// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterStates.h"
#include "GameplayTagAssetInterface.h"
#include "Interface/TargetingInterface.h"
#include "Interface/CombatInterface.h"
#include "Components/TimelineComponent.h"
#include "BaseCharacter.generated.h"



class UTimelineComponent;
class USpringArmComponent;
class UCameraComponent;
class UCombatComponent;
class UStateComponent;
class UTargetComponent;
class UEquipmentComponent;

UCLASS()
class MELEECOMBAT_API ABaseCharacter : public ACharacter, public IGameplayTagAssetInterface, public ITargetingInterface,
	public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ContinueAttack();
	void ResetCombat();
	void PointDamage();

	bool CanPerformToggleCombat();
	bool CanPerformAttack();
	bool CanPerformDodge();
	bool CanPerformSprinting();
	bool CanPerformBlock();
	bool CanJump();
	bool CanBlockAttack();

	void SetMovementSpeedMode(ESpeedMode NewSpeedMode);
	FORCEINLINE ESpeedMode GetMovementSpeedMode() { return SpeedMode; }
	FGameplayTag GetDesiredAttackType();
	void Attack();
	void ChargeAttack();
	bool ResetChargeAttack();
	void SprintingStaminaCost();
	bool SprintingTimer();
	void DisableSprinting(bool IsForceExitSprinting);
	void ChargeAttacktimer(float PressTime);
	void EnableRagdoll();
	FORCEINLINE EHitDirection GetHitDirection() { return HitDirection; }
	void ApplyHitReactionPhysicsVeclocity(float InitialSpeed);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UPROPERTY()
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY()
	TObjectPtr<UCameraComponent> ViewCamera;

	FGameplayTagContainer OwnedGameplayTags;
	FGameplayTagContainer IgnoreGameplayTags;

	float MaxWalkingSpeed;
	float MaxJogginSepeed;
	float MaxSprintingSpeed;

	UPROPERTY()
	TObjectPtr<UAnimMontage> UnarmHitMontage_F;
	UPROPERTY()
	TObjectPtr<UAnimMontage> UnarmHitMontage_B;
	UPROPERTY()
	TObjectPtr<UAnimMontage> UnarmHitMontage_L;
	UPROPERTY()
	TObjectPtr<UAnimMontage> UnarmHitMontage_R;
	UPROPERTY()
	TObjectPtr<UAnimMontage> KnockdownMontage_F;
	UPROPERTY()
	TObjectPtr<UAnimMontage> KnockdownMontage_B;

	FName PelvisBoneName;
	ESpeedMode SpeedMode;
	bool bCanMove;
	bool bIsCharged;
	bool bIsHeavyAttack;
	bool bIsForceExitSprinting;

	float ChargeTime;
	float ChargeAttackTime;
	float SprintingInputDeltaTime;

	EHitDirection HitDirection;


	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent;
	UPROPERTY()
	TObjectPtr<UStateComponent> StateComponent;
	UPROPERTY()
	TObjectPtr<UTargetComponent> TargetingComponent;
	UPROPERTY()
	TObjectPtr<UEquipmentComponent> EquipmentComponent;


	float DeltaTime;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* ExampleTimelineComp;

public:
	UPROPERTY(EditAnywhere)
	UCurveFloat* TimelineCurve;

private:
	UPROPERTY()
	UTimelineComponent* RotateToTargetTimeLineComponent;
	UPROPERTY(EditAnywhere, Category = "Timeline")
	FTimeline RotateToTargetTimeLine;

	FOnTimelineFloat RotateToTargetTimeLineUpdateDelegate;

	UFUNCTION()
	void RotateToTargetUpdate(float Output);


	// Inherited via ITargetingInterface
	bool CanbeTargeted() override;
	void EnableLockOn(bool EnableLockon) override;
	void OnTargeted(bool IsTargeted) override;

	// Inherited via ICombatInterface
	void RotateToActor(AActor* Excutor) override;
	void JumpTo(float FlightTime) override;
	void MoveTo(FVector Start, FVector End) override;
	void ConsumeItem() override;
	bool CanRecieveDamage() override;
	void SetMoveable(bool CanMove) override;
	FRotator GetDesireRotation() override;
	ESpeedMode GetSpeedMode() override;
	void PerformDeath(TArray<AActor*>& ActorToDestory, float& Duration) override;
	bool PerformHitReaction(EDamegeType DamageType, FVector HitLocation, float Damage) override;
	bool PerformUseItem(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, OUT float& ActionDuration) override;
	bool PerformAction(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, OUT float& ActionDuration) override;

	// Inherited via ICombatInterface
	bool PerformAttack(FGameplayTag AttackType, int MontageIndex, bool isRandomIndex, bool isCalledbyAI, float PlayRate, OUT float& ActionDuration) override;
};
