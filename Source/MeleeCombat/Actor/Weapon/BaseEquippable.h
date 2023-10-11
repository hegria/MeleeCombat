// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "BaseEquippable.generated.h"

UCLASS()
class MELEECOMBAT_API ABaseEquippable : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquippable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AttachAttactor(FName SocketName);

	virtual void OnEquipped();
	virtual void OnUnequipped();
	
	void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	FORCEINLINE bool GetIsEquipped() { return bIsEquipped; }
	FORCEINLINE void SetIsEquipped(bool isEquippeed) { bIsEquipped = isEquippeed; }

	FORCEINLINE TObjectPtr<UStaticMesh> GetItemMesh() { return ItemStaticMesh; }

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> ItemSkeletalMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> ItemStaticMesh;

	UPROPERTY(EditAnywhere)
	FName AttachSocketName;

	bool bIsEquipped;

	FGameplayTagContainer OwnedGameplayTagContainer;
};
