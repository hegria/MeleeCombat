// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "CombatComponent.generated.h"


class ABaseWeapon;
class ABaseConsumeable;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBAT_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCombatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMainWeapon(TObjectPtr<ABaseWeapon> NewMainWeapon);
	void SetShildWeapon(TObjectPtr<ABaseWeapon> NewShieldWeapon);
	void SetItem(TObjectPtr<ABaseConsumeable> NewItem);
	void SetCombatEnable(bool isCombatEnable);
	void ResetAttack();
	void SetBlockingEnable(bool isBlockingEnable);
	void ConsumeItem();


	FORCEINLINE TObjectPtr<ABaseWeapon> GetMainWeapon() { return MainWeapon; };
	FORCEINLINE TObjectPtr<ABaseWeapon> GetShieldWeapon() { return ShieldWeapon; };
	FORCEINLINE TObjectPtr<ABaseConsumeable> GetItem() { return Item; };
	FORCEINLINE bool IsCombatEnable() { return bIsCombatEnable; };
	FORCEINLINE bool IsBlockingEnable() { return bIsBlockingEnable; };
	
	int AttackCount;

private:
	UPROPERTY()
	TObjectPtr<ABaseWeapon> MainWeapon;
	UPROPERTY()
	TObjectPtr<ABaseWeapon> ShieldWeapon;
	UPROPERTY()
	TObjectPtr<ABaseConsumeable> Item;
	
	bool bIsCombatEnable;
	bool bIsAttackSaved;
	bool bIsBlockingEnable;
	bool bIsWaitForAttack;

	// TODO Callback
};
