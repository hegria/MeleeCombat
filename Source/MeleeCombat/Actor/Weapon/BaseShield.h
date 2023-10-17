// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "BaseShield.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API ABaseShield : public ABaseWeapon
{
	GENERATED_BODY()
	
	virtual void OnEquipped() override;
	virtual void OnUnequipped() override;


};
