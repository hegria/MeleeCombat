// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/BaseEquippable.h"
#include "GameFramework/Character.h"
#include "Component/CollisionComponent.h"


// Sets default values
ABaseEquippable::ABaseEquippable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	RootComponent = ItemStaticMesh;
}

// Called when the game starts or when spawned
void ABaseEquippable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEquippable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEquippable::AttachAttactor(FName SocketName)
{
	
	ACharacter* character = Cast<ACharacter>(GetOwner());
	FAttachmentTransformRules rule = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(character->GetMesh(), rule, SocketName);
}

void ABaseEquippable::OnEquipped()
{
	bIsEquipped = true;
	AttachAttactor(AttachSocketName);
}

void ABaseEquippable::OnUnequipped()
{
	bIsEquipped = false;

}

void ABaseEquippable::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = OwnedGameplayTagContainer;
}

