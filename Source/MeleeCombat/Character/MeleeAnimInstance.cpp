// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MeleeAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMeleeAnimInstance::NativeInitializeAnimation()
{
	Character = Cast<ABaseCharacter>(GetOwningActor());

	CharacterMovementComponent = Character->GetCharacterMovement();

}

void UMeleeAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Velocity = CharacterMovementComponent->Velocity;
	GroundSpeed = Velocity.Size2D();
	Direction = CalculateDirection(Velocity, Character->GetActorRotation());
	bShouldMove = GroundSpeed > 0 && CharacterMovementComponent->GetCurrentAcceleration() != FVector::Zero();
	bIsFalling = CharacterMovementComponent->IsFalling();
}
