// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseConsumeable.h"
#include "Component/CombatComponent.h"

void ABaseConsumeable::OnEquipped()
{
	GetOwner()->GetComponentByClass<UCombatComponent>()->SetItem(this);
}

void ABaseConsumeable::OnUnequipped()
{
	Super::OnUnequipped();
	GetOwner()->GetComponentByClass<UCombatComponent>()->SetItem(nullptr);
}

void ABaseConsumeable::OnItemConsumed()
{
	NumberInBagpack -= NumberOfUsed;
	NumberInBagpack = FMath::Max(0, NumberInBagpack);

	// TODO CallBack
}

bool ABaseConsumeable::GetRemainingItemsCount(int& OutNumberInBackpack)
{
	OutNumberInBackpack = NumberInBagpack;

	return NumberInBagpack >= NumberOfUsed;
}
