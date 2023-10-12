// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/BaseEquippable.h"
#include "BaseConsumeable.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API ABaseConsumeable : public ABaseEquippable
{
	GENERATED_BODY()
	

public:

	void OnEquipped() override;
	void OnUnequipped() override;
	void OnItemConsumed();

	FORCEINLINE TArray<UAnimMontage*> GetUseItemMontages() { return UseItemMontages; }
	bool GetRemainingItemsCount(int& OutNumberInBackpack);
	UPROPERTY()
	TArray<UAnimMontage*> UseItemMontages;
	
	int NumberOfUsed;
	int NumberInBagpack;

};
