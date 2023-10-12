// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MeleePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/MeleeInputComponent.h"
#include "Character/BaseCharacter.h"
#include "Component/TargetComponent.h"
#include "InputActionValue.h"

void AMeleePlayerController::BeginPlay()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
		Subsystem->AddMappingContext(MeleeContext, 0);

	PlayerCharacter = Cast<ABaseCharacter>(GetCharacter());

}

void AMeleePlayerController::SetupInputComponent()
{
	UMeleeInputComponent* MeleeInputComponent = CastChecked<UMeleeInputComponent>(InputComponent);
	MeleeInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMeleePlayerController::Move);
	MeleeInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMeleePlayerController::Look);

	MeleeInputComponent->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagStarted,
		&ThisClass::AbilityInputTagCompleted,
		&ThisClass::AbilityInputTagTriggered);

}

void AMeleePlayerController::PlayerTick(float DeltaTime)
{

}

void AMeleePlayerController::Move(const FInputActionValue& value)
{

}

void AMeleePlayerController::Look(const FInputActionValue& value)
{
	const FVector2D InputVector = value.Get<FVector2D>();

	float YVal = InputVector.Y;

	if (PlayerCharacter->TargetingComponent->IsTargeting())
	{
		YVal *= 0.2;
	}
	else
	{
		AddYawInput(InputVector.X);
	}

	AddPitchInput(YVal);
}

void AMeleePlayerController::AbilityInputTagStarted(FGameplayTag InputTag)
{

}

void AMeleePlayerController::AbilityInputTagCompleted(FGameplayTag InputTag)
{

}

void AMeleePlayerController::AbilityInputTagTriggered(FGameplayTag InputTag)
{

}
