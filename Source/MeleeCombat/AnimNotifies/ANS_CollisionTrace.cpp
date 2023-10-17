// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ANS_CollisionTrace.h"
#include "Component/CombatComponent.h"
#include "Actor/Weapon/BaseWeapon.h"


void UANS_CollisionTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>();
	if (Combat && Combat->GetMainWeapon().Get())
	{
		Combat->GetMainWeapon()->ActivateCollision(CollisionPart);
	}
}

void UANS_CollisionTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>();
	if (Combat && Combat->GetMainWeapon().Get())
	{
		Combat->GetMainWeapon()->DeactivateCollision(CollisionPart);
	}
}
