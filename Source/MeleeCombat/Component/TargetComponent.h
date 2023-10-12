// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/CharacterStates.h"
#include "TargetComponent.generated.h"

class AController;
class ACharacter;
class UCameraComponent;
class UCombatComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBAT_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	void SetIsTargeting(bool IsTargeting);
	bool FindTarget(OUT AActor* Result);
	void SetTargetActor(AActor* NewTargetActor);
	void UpdateTargetingControlRotation();
	bool CanTargetActor(AActor* InTargetActor);
	void SetRotationMode(ERotationMode NewRotationMode);
	void UpdateRotationMode();
	void EnableLockOn(bool CalledByAI);
	void DisableLockOn();
	void ToggleLockOn();

	FORCEINLINE bool IsTargeting() { return bIsTargeting; };
	FORCEINLINE TObjectPtr<AActor> GetTargetActor() { return TargetActor; };
	FORCEINLINE ERotationMode GetRotationMode() { return CurrentRotationMode; };

protected:
	TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectType;
	float TargetingRadius;
	float TargetingDistance;
	float TargetRotationInterpSpeed;
	float DefulatRotationMode;
	
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	UPROPERTY()
	TObjectPtr<UCameraComponent> FollowCamera;
	UPROPERTY()
	TObjectPtr<UCombatComponent> OwnerCombatComponent;
	UPROPERTY()
	TObjectPtr<AController> OwnerController;
	bool bIsTargeting;
	UPROPERTY()
	TObjectPtr<AActor> TargetActor;
	ERotationMode CurrentRotationMode;

};
