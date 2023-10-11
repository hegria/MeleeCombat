// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseWeapon.h"
#include "Component/CombatComponent.h"
#include "Component/CollisionComponent.h"

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
	SetIsEquipped(true);

	CombatComponent = GetOwner()->GetComponentByClass<UCombatComponent>();

}

