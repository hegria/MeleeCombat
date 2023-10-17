// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_EnableLockOn.h"
#include "Interface/TargetingInterface.h"

void UAN_EnableLockOn::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto Target = Cast<ITargetingInterface>(MeshComp->GetOwner());
	if (Target)
	Target->EnableLockOn(EnableLockOn);
}
