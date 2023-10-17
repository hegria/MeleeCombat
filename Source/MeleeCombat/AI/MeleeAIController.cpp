// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MeleeAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayTagAssetInterface.h"
#include "MeleeGameplayTags.h"
#include "Character/BaseCharacter.h"
#include "Component/CombatComponent.h"
#include "Component/TargetComponent.h"

AMeleeAIController::AMeleeAIController()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(FName("AIPerception"));
}

void AMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto BB = Blackboard.Get();

	if (UseBlackboard(BlackboardData, BB))
	{
		RunBehaviorTree(BehaviorTree);
	}

	auto BaseCharacter = Cast<ABaseCharacter>(InPawn);
	BaseCharacter->CombatComponent->ToggledCombat.BindUFunction(this, FName("SetBlackBoardCombatEnable"));
	BaseCharacter->TargetingComponent->DisabledLockOn.BindUFunction(this, FName("OnDisableTargeting"));

	AIPerception->OnPerceptionUpdated.AddDynamic(this, &AMeleeAIController::UpdatePerception);

}

void AMeleeAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AMeleeAIController::UpdatePerception(const TArray<AActor*>& UpdatedActors)
{
	for (auto actor : UpdatedActors)
	{
		FActorPerceptionBlueprintInfo info;
		AIPerception->GetActorsPerception(actor, info);
		for (int i = 0; i < 2; i++)
		{
			if (info.LastSensedStimuli[i].WasSuccessfullySensed()) 
			{
				auto TagsInterface = Cast<IGameplayTagAssetInterface>(actor);
				FString str = actor->GetName();
				if (TagsInterface == nullptr) return;

				if (TagsInterface->HasMatchingGameplayTag(GET_MELEE_TAG.Player))
				{
					SetBlackBoardTargetActor(actor);
				}

			}
		}
	}
}

void AMeleeAIController::SetBlackBoardCombatEnable(bool CombatEnabled)
{
	Blackboard->SetValueAsBool(FName("bCombatEnable"), CombatEnabled);
}

void AMeleeAIController::SetBlackBoardTargetActor(AActor* Target)
{
	Blackboard->SetValueAsObject(FName("Target"), Target);
}

void AMeleeAIController::OnDisableTargeting()
{
	SetBlackBoardTargetActor(nullptr);
}
	