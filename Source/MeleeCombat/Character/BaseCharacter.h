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
class UAbilitySystemComponent;
class UGameplayEffect;
class UGameplayAbility;
class UMeleeAttributeSet;

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
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	void ContinueAttack();
	void ResetCombat();
	void SetMovable(bool CanMove);
	void BeginRotateToTarget();
	void StopRotateToTarget();
	void Landed(const FHitResult& Hit) override;

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
	void ApplyHitReactionPhysicsVeclocity(float InitialSpeed);
	EHitDirection GetHitDirection(FVector HitLocation);
	void ModifyStamina(float amt);
	
	UFUNCTION()
	void RotateToTargetUpdate(float Output);
	UFUNCTION()
	void MoveToTargetupdate(float Output);

	virtual void InitAbilityActorInfo() {};

	void InitializeDefaultAttributes();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level);
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayTag Tag, float amt);

	// Inherited via ITargetingInterface
	bool CanbeTargeted() override;
	void EnableLockOn(bool EnableLockon) override;
	void OnTargeted(bool IsTargeted) override;
	// Inherited via ICombatInterface
	void RotateToActor(AActor* Excutor) override;
	void MoveTo(FVector Start, FVector End) override;
	void ConsumeItem() override;
	bool CanRecieveDamage() override;
	void SetMoveable(bool CanMove) override;
	FRotator GetDesireRotation() override;
	ESpeedMode GetSpeedMode() override;
	void PerformDeath(TArray<AActor*>& ActorToDestory, float& Duration) override;
	bool PerformHitReaction(EDamageType DamageType, FVector HitLocation, float Damage) override;
	bool PerformUseItem(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, OUT float& ActionDuration) override;
	UFUNCTION(BlueprintCallable)
	bool PerformAction(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, float& ActionDuration) override;
	// Inherited via ICombatInterface
	UFUNCTION(BlueprintCallable)
	bool PerformAttack(FGameplayTag AttackType, int MontageIndex, bool isRandomIndex, bool isCalledbyAI, float PlayRate, float& ActionDuration) override;
	void HandlePointDamage(const FHitResult& HitInfo, float Damage, EDamageType DamageType, FVector HitLocation) override;

	UFUNCTION()
	virtual void OnCharacterActionBegin(const FGameplayTag& Action);
	UFUNCTION()
	virtual void OnCharacterActionEnd(const FGameplayTag& Action);
	UFUNCTION()
	void OnCharacterStateBegin(const FGameplayTag& Action);
	UFUNCTION()
	void OnCharacterStateEnd(const FGameplayTag& Action);

	float DeltaTime;


	UPROPERTY(EditAnywhere, Category = "GameplayTags")
	FGameplayTagContainer OwnedGameplayTags;
	UPROPERTY(EditAnywhere, Category = "GameplayTags")
	FGameplayTagContainer IgnoreGameplayTags;

	UPROPERTY(EditAnywhere, Category = "MovemntSpeed")
	float MaxWalkingSpeed;
	UPROPERTY(EditAnywhere, Category = "MovemntSpeed")
	float MaxJogginSepeed;
	UPROPERTY(EditAnywhere, Category = "MovemntSpeed")
	float MaxSprintingSpeed;

	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> UnarmHitMontage_F;
	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> UnarmHitMontage_B;
	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> UnarmHitMontage_L;
	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> UnarmHitMontage_R;
	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> KnockdownMontage_F;
	UPROPERTY(EditAnywhere, Category = "Montages")
	TObjectPtr<UAnimMontage> KnockdownMontage_B;

	FName PelvisBoneName;
	ESpeedMode SpeedMode;
	UPROPERTY(EditAnywhere)
	bool bCanMove;
	UPROPERTY(EditAnywhere)
	bool bIsCharged;
	UPROPERTY(EditAnywhere)
	bool bIsHeavyAttack;
	UPROPERTY(EditAnywhere)
	bool bIsForceExitSprinting;
	float ChargeTime;
	UPROPERTY(EditAnywhere)
	float ChargeAttackTime;
	float SprintingInputDeltaTime;

	EHitDirection HitDirection;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> CameraBoom;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> ViewCamera;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCombatComponent> CombatComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UStateComponent> StateComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTargetComponent> TargetingComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UEquipmentComponent> EquipmentComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	UPROPERTY()
	UTimelineComponent* RotateToTargetTimeLineComponent;
	
	// Timeline
public:
	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* TimelineCurve;
	UPROPERTY()
	FTimeline MoveToTargetTimeLine;
	FOnTimelineFloat RotateToTargetTimeLineUpdateDelegate;
	FOnTimelineFloat MoveToTargetTimeLineUpdateDelegate;
	FVector StartMoveTo;
	FVector EndMoveTo;

public:
	UPROPERTY(EditAnywhere, Category = "Abilities")
	float StaminaRegenRate;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> UseStaminaEffect;
	UPROPERTY()
	TObjectPtr<UMeleeAttributeSet> AttributeSet;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;
};
