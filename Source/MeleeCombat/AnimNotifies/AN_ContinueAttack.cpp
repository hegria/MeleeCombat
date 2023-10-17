// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_ContinueAttack.h"
#include "Interface/CombatInterface.h"

void UAN_ContinueAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (Combat)
	Combat->ContinueAttack();
}
