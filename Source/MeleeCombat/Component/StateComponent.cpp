// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StateComponent.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStateComponent::SetCurrentState(FGameplayTag NewTag)
{
	if (CurrentState != NewTag)
	{
		OnCharacterStateEnd.Execute(CurrentState);
		CurrentState = NewTag;
		OnCharacterStateBegin.Execute(CurrentState);
	}
}

void UStateComponent::SetCurrentAction(FGameplayTag NewTag)
{
	if (CurrentCharacterAction != NewTag)
	{
		OnCharacterActionEnd.Execute(CurrentCharacterAction);
		CurrentCharacterAction = NewTag;
		OnCharacterActionBegin.Execute(CurrentCharacterAction);
	}
}

void UStateComponent::ResetState()
{
	SetCurrentState(FGameplayTag::EmptyTag);
}

bool UStateComponent::IsCurrentStateEqualToAny(FGameplayTagContainer CheckTag)
{
	return CurrentState.MatchesAnyExact(CheckTag);
}

bool UStateComponent::IsCurrentActionEqualToAny(FGameplayTagContainer CheckTag)
{
	return CurrentCharacterAction.MatchesAnyExact(CheckTag);
}

