// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MeleePlayer.h"
#include "Controller/MeleePlayerController.h"

void AMeleePlayer::InitAbilityActorInfo()
{

}

void AMeleePlayer::BeginPlay()
{
	Super::BeginPlay();
	Cast<AMeleePlayerController>(GetController())->InitHUD();
}
