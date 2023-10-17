// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CollisionComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/CombatInterface.h"
#include "GameplayTagAssetInterface.h"

// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (bCollisionEnabled)
	{

		TArray<FHitResult> OutHits;

		bool isHit = UKismetSystemLibrary::SphereTraceMultiForObjects(this,
			CollisionMeshComponent->GetSocketLocation(StartSocketName),
			CollisionMeshComponent->GetSocketLocation(EndSocketName),
			TraceRadius,
			CollisionObjectType,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::None,
			OutHits,
			true
		);


		if (isHit)
		{
			for (auto hit : OutHits) {
				LastHit = hit;
				if (!AlreadyHitActors.Contains(hit.GetActor())
					&& !Cast<IGameplayTagAssetInterface>(hit.GetActor())->HasMatchingGameplayTag(IgnoreGamePlayTag))
				{
					AlreadyHitActors.Add(hit.GetActor());
					ICombatInterface* combatAPI = Cast<ICombatInterface>(hit.GetActor());
					if (combatAPI) {
						// Apply Effect
						OnHit.Execute(hit);
					}
				}
				
			}
		}

	}

}

void UCollisionComponent::ActivateCollision()
{
	AlreadyHitActors.Empty();
	bCollisionEnabled = true;
}

void UCollisionComponent::DeactivateCollision()
{
	bCollisionEnabled = false;
}

