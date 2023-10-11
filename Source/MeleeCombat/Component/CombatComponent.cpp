// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CombatComponent.h"
#include "GameFramework/Character.h"
#include "Character/MeleeAnimInstance.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Actor/Weapon/BaseConsumeable.h"

// Sets default values for this component's properties
UCombatComponent::UCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UCombatComponent::SetMainWeapon(TObjectPtr<ABaseWeapon> NewMainWeapon)
{
	if (MainWeapon.Get()) {
		MainWeapon->OnUnequipped();
		MainWeapon->Destroy();
	}

	MainWeapon = NewMainWeapon;
}

void UCombatComponent::SetShildWeapon(TObjectPtr<ABaseWeapon> NewShieldWeapon)
{
	ShieldWeapon = NewShieldWeapon;
}

void UCombatComponent::SetItem(TObjectPtr<ABaseConsumeable> NewItem)
{
	Item = NewItem;
	//TODO
}

void UCombatComponent::SetCombatEnable(bool isCombatEnable)
{
	bIsCombatEnable = isCombatEnable;

	ACharacter* Char = Cast<ACharacter>(GetOwner());
	UMeleeAnimInstance* Anim = Cast<UMeleeAnimInstance>(Char->GetMesh()->GetAnimInstance());

	Anim->SetIsCombatEnabled(isCombatEnable);

	//TODO AI
}

void UCombatComponent::ResetAttack()
{
	AttackCount = 0;
	bIsAttackSaved = false;
	bIsWaitForAttack = false;
}

void UCombatComponent::SetBlockingEnable(bool isBlockingEnable)
{
	if (isBlockingEnable != bIsBlockingEnable)
	{
		bIsBlockingEnable = isBlockingEnable;

		ACharacter* Char = Cast<ACharacter>(GetOwner());
		UMeleeAnimInstance* Anim = Cast<UMeleeAnimInstance>(Char->GetMesh()->GetAnimInstance());

		Anim->SetIsBlockingEnabled(bIsBlockingEnable);
	}
}

void UCombatComponent::ConsumeItem()
{
	Item->OnItemConsumed();
}

