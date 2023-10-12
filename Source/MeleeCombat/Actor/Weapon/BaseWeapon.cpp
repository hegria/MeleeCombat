// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"
#include "Component/CombatComponent.h"
#include "Component/StateComponent.h"
#include "Component/CollisionComponent.h"
#include "GameFramework/Character.h"
#include "Character/MeleeAnimInstance.h"
#include "Interface/CombatInterface.h"
#include "MeleeGameplayTags.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComponent"));
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::OnEquipped()
{	
	Super::OnEquipped();
	CombatComponent = GetOwner()->GetComponentByClass<UCombatComponent>();
	StateComponent = GetOwner()->GetComponentByClass<UStateComponent>();

	CombatComponent->SetMainWeapon(this);
	Cast<UMeleeAnimInstance>(Cast<ACharacter>(GetOwner())->GetMesh()->GetAnimInstance())
		->SetCombatType(CombatType);
	CollisionComponent->SetCollisionMeshComponent(ItemStaticMesh);
	CollisionComponent->AddActorsToIgnore(GetOwner());
}

void ABaseWeapon::OnHit(FHitResult OnHit)
{
	if (Cast<ICombatInterface>(OnHit.GetActor())->CanRecieveDamage())
	{
		// Todo Apply PointDamage
	}
}

void ABaseWeapon::SimulateWeaponPhysics()
{
	ItemStaticMesh->SetCollisionProfileName(FName("PhysicsActor"));
	ItemStaticMesh->SetSimulatePhysics(true);
}

void ABaseWeapon::ToggleCombat(bool EnableCombat)
{
	CombatComponent->SetCombatEnable(EnableCombat);
}

TArray<UAnimMontage*>ABaseWeapon::GetActionMontage(FGameplayTag Tag)
{
	TArray<UAnimMontage*> ReturnMontage;

	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_Attack_LightAttack))
	{
		return LightAttackMontage;
	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_Attack_HeavyAttack))
	{
		return HeavyAttackMontage;
	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_Attack_ChargedAttack))
	{
		return ChargedAttackMontage;

	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_Attack_FallingAttack))
	{
		return FallingAttackMontage;
	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_Dodge))
	{
		return DodgeMontage;
	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_Die))
	{
		return DieMontage;
	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_EnterCombat))
	{
		ReturnMontage.Add(EnterCombat);
	}
	if (Tag.MatchesTagExact(FMeleeGameplayTags::Get().Action_ExitCombat))
	{
		ReturnMontage.Add(ExitCombat);
	}
	return ReturnMontage;
}

void ABaseWeapon::ActivateCollision()
{
	CollisionComponent->ActivateCollision();
}

void ABaseWeapon::DeactivateCollision()
{
	CollisionComponent->DeactivateCollision();
}

