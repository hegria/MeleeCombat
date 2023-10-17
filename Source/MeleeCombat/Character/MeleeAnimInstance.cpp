// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MeleeAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/CombatComponent.h"

void UMeleeAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Character)
	{
		CharacterMovementComponent = Character->GetCharacterMovement();
	}

}

void UMeleeAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (CharacterMovementComponent)
	{
		Velocity = CharacterMovementComponent->Velocity;
		GroundSpeed = Velocity.Size2D();
		Direction = UKismetAnimationLibrary::CalculateDirection(Velocity, Character->GetActorRotation());
		bShouldMove = GroundSpeed > 0 && CharacterMovementComponent->GetCurrentAcceleration() != FVector::Zero();
		bIsFalling = CharacterMovementComponent->IsFalling();
		bBlockingEnabled = Character->CombatComponent->IsBlockingEnable();
	}
}
