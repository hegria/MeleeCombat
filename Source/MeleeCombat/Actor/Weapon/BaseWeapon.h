// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor/Weapon/BaseEquippable.h"
#include "BaseWeapon.generated.h"

class UAnimMontage;
class UCollisionComponent;
class UCombatComponent;

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

private:

	UPROPERTY(EditAnywhere)
	FName HandSocketName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> EnterCombat;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UAnimMontage> ExitCombat;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AttackMontage;
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> DodgeMontage;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCollisionComponent> CollisionComponent;

	UPROPERTY()
	TObjectPtr<UCombatComponent> CombatComponent;
};
