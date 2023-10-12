// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "StateComponent.generated.h"


DECLARE_DELEGATE_OneParam(FOnStateChanged, const FGameplayTag&)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBAT_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetCurrentState(FGameplayTag NewTag);
	void SetCurrentAction(FGameplayTag NewTag);
	void ResetState();
	FORCEINLINE FGameplayTag GetCurrentState() { return CurrentState; };
	FORCEINLINE FGameplayTag GetCurrentAction() { return CurrentCharacterAction; };
	bool IsCurrentStateEqualToAny(FGameplayTagContainer CheckTag);
	bool IsCurrentActionEqualToAny(FGameplayTagContainer CheckTag);

	FOnStateChanged OnCharacterStateBegin;
	FOnStateChanged OnCharacterStateEnd;
	FOnStateChanged OnCharacterActionBegin;
	FOnStateChanged OnCharacterActionEnd;

private:
	FGameplayTag CurrentState;
	FGameplayTag CurrentCharacterAction;

};
