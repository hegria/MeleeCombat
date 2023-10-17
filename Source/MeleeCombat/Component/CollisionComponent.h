// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CollisionComponent.generated.h"

DECLARE_DELEGATE_OneParam(FONHIT, const FHitResult&)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBAT_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ActivateCollision();
	void DeactivateCollision();

	FORCEINLINE void AddActorsToIgnore(AActor* actor) { ActorsToIgnore.AddUnique(actor); }
	FORCEINLINE void RemoveActorsToIgnore(AActor* actor) { ActorsToIgnore.Remove(actor); }


	FORCEINLINE TArray<AActor*> GetAlreadyHitActors() { return AlreadyHitActors; }
	FORCEINLINE TArray<AActor*> GetActorsToIgnore() { return ActorsToIgnore; }
	FORCEINLINE bool GetCollisionEnabled() { return bCollisionEnabled; }
	FORCEINLINE FHitResult GetLastHit() { return LastHit; }
	FORCEINLINE TObjectPtr<UMeshComponent> GetCollisionMeshComponent() { return CollisionMeshComponent; }
	FORCEINLINE void SetCollisionMeshComponent(TObjectPtr<UMeshComponent> _CollisionMeshComponent) { this->CollisionMeshComponent = _CollisionMeshComponent; }

	FONHIT OnHit;

private:
	UPROPERTY()
	TObjectPtr<UMeshComponent> CollisionMeshComponent;
	

	UPROPERTY(EditAnywhere);
	FName StartSocketName;
	UPROPERTY(EditAnywhere);
	FName EndSocketName;
	UPROPERTY(EditAnywhere);
	float TraceRadius;
	UPROPERTY(EditAnywhere);
	TArray<TEnumAsByte<EObjectTypeQuery>> CollisionObjectType;
	UPROPERTY(EditAnywhere);
	TArray<AActor *> ActorsToIgnore;
	UPROPERTY(EditAnywhere);
	FGameplayTag IgnoreGamePlayTag;

	bool bCollisionEnabled;
	UPROPERTY()
	TArray<AActor *> AlreadyHitActors;
	UPROPERTY()
	FHitResult LastHit;
	TObjectPtr<AActor> HitActor;
		
};
