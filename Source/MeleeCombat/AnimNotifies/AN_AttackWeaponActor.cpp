// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AN_AttackWeaponActor.h"
#include "Component/CombatComponent.h"
#include "Actor/Weapon/BaseWeapon.h"

void UAN_AttackWeaponActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto Combat = MeshComp->GetOwner()->GetComponentByClass<UCombatComponent>();

	if (Combat &&Combat->GetMainWeapon().Get())
	{
		Combat->GetMainWeapon()->AttachAttactor(AttackSocketName);
	}
}
