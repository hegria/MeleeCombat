// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_RotateCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UANS_RotateCharacter : public UAnimNotifyState
{
	GENERATED_BODY()
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);

	float InterpSpeed = 720;
};
