// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MeleeAIController.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API AMeleeAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMeleeAIController();
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	UFUNCTION()
	void UpdatePerception(const TArray<AActor*>& UpdatedActors);
	UFUNCTION()
	void SetBlackBoardCombatEnable(bool CombatEnabled);
	void SetBlackBoardTargetActor(AActor* Target);
	UFUNCTION()
	void OnDisableTargeting();
private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere)
	class UBlackboardData* BlackboardData;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UAIPerceptionComponent> AIPerception;
};
