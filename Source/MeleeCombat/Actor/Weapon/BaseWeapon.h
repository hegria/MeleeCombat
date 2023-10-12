// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor/Weapon/BaseEquippable.h"
#include "Character/CharacterStates.h"
#include "BaseWeapon.generated.h"

class UAnimMontage;
class UCollisionComponent;
class UCombatComponent;
class UStateComponent;

UCLASS()
class MELEECOMBAT_API ABaseWeapon : public ABaseEquippable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnEquipped() override;
	virtual void OnHit(FHitResult OnHit);
	void SimulateWeaponPhysics();
	void ToggleCombat(bool EnableCombat);
	virtual TArray<UAnimMontage*> GetActionMontage(FGameplayTag Tag);
	void ActivateCollision();
	void DeactivateCollision();

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitMontage_F;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitMontage_B;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitMontage_L;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> HitMontage_R;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> KnockdownMontage_F;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> KnockdownMontage_B;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DefenseHitMontage;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> DefenseHitBrokenMontage;

private:

	ECombatType CombatType;

	UPROPERTY(EditAnywhere)
	FName HandSocketName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EnterCombat;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ExitCombat;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> LightAttackMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> HeavyAttackMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> ChargedAttackMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> FallingAttackMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> SprintingAttackMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> DodgeMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> DieMontage;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, float> ActionStateCost;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStateComponent> StateComponent;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCollisionComponent> CollisionComponent;
	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent;
};
