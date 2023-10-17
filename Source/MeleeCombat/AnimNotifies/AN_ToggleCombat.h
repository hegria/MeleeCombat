// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_ToggleCombat.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UAN_ToggleCombat : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEnableCombat;
};
