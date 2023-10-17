// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_DisableMovement.h"
#include "Interface/CombatInterface.h"

void UANS_DisableMovement::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (Combat)
	Combat->SetMoveable(false);
}

void UANS_DisableMovement::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (Combat)
	{
		Combat->SetMoveable(true);

	}
}
