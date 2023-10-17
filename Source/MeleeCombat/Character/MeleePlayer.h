// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "MeleePlayer.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API AMeleePlayer : public ABaseCharacter
{
	GENERATED_BODY()
	virtual void InitAbilityActorInfo() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
