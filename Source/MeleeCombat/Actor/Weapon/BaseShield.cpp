// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseShield.h"
#include "Component/CombatComponent.h"
#include "Component/CollisionComponent.h"
#include "Component/StateComponent.h"
#include "Character/MeleeAnimInstance.h"
#include "GameFramework/Character.h"
#include "Character/CharacterStates.h"

void ABaseShield::OnEquipped()
{
	bIsEquipped = true;
	AttachAttactor(AttachSocketName);

	CombatComponent = GetOwner()->GetComponentByClass<UCombatComponent>();
	StateComponent = GetOwner()->GetComponentByClass<UStateComponent>();
	CombatComponent->SetShildWeapon(this);
	Cast<UMeleeAnimInstance>(Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance())
		->SetCombatType(CombatType);
	CollisionComponent->SetCollisionMeshComponent(ItemStaticMesh);
	CollisionComponent->AddActorsToIgnore(GetOwner());
}

void ABaseShield::OnUnequipped()
{
	Super::OnUnequipped();
	CombatComponent->SetShildWeapon(nullptr);
}
