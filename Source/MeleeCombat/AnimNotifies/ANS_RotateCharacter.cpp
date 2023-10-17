// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_RotateCharacter.h"
#include "Interface/CombatInterface.h"

void UANS_RotateCharacter::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (Combat)
	{
		FRotator Target = Combat->GetDesireRotation();

		MeshComp->GetOwner()->SetActorRotation(
			FMath::RInterpConstantTo(MeshComp->GetOwner()->GetActorRotation(), Target, FrameDeltaTime, InterpSpeed)
		);
	}
}
