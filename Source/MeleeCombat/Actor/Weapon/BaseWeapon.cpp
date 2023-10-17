// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"
#include "Component/CombatComponent.h"
#include "Component/StateComponent.h"
#include "Component/CollisionComponent.h"
#include "GameFramework/Character.h"
#include "Character/MeleeAnimInstance.h"
#include "Interface/CombatInterface.h"
#include "MeleeGameplayTags.h"
#include "Particles/ParticleSystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComponent"));
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetupAttachment(ItemStaticMesh);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnHit.BindUFunction(this, FName("OnHit"));
	
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

void ABaseWeapon::OnHit(const FHitResult& OnHit)
{
	auto Combat = Cast<ICombatInterface>(OnHit.GetActor());
	if (Combat->CanRecieveDamage())
	{
		// Todo Apply PointDamage
		UAbilitySystemComponent* TargetASC =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OnHit.GetActor());
		if (TargetASC == nullptr) return;

		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(AttackEffect, 1, EffectContextHandle);
		EffectSpecHandle.Data->SetByCallerTagMagnitudes.Add(GET_MELEE_TAG.Attributes_Amt_Health, -Damage);
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		Combat->HandlePointDamage(OnHit, Damage, DamageType, GetOwner()->GetActorLocation());
		UGameplayStatics::ApplyDamage(OnHit.GetActor(), Damage, GetInstigatorController(), GetOwner(), UDamageType::StaticClass());
		
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

void ABaseWeapon::ActivateCollision(ECollisionPart CollsionPart)
{
	CollisionComponent->ActivateCollision();
}

void ABaseWeapon::DeactivateCollision(ECollisionPart CollsionPart)
{
	CollisionComponent->DeactivateCollision();
}

