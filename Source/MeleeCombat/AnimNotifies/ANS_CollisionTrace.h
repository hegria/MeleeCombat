// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Character/CharacterStates.h"
#include "ANS_CollisionTrace.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UANS_CollisionTrace : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
public:
	ECollisionPart CollisionPart = ECollisionPart::ECP_MainWeapon;
};
