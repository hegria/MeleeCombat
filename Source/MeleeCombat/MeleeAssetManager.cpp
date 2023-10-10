// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAssetManager.h"
#include "MeleeGameplayTags.h"
#include "AbilitySystemGlobals.h"

UMeleeAssetManager& UMeleeAssetManager::Get()
{
	check(GEngine);


	UMeleeAssetManager* MeleeAssetManager = Cast<UMeleeAssetManager>
		(GEngine->AssetManager);
	return *MeleeAssetManager;
}

void UMeleeAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMeleeGameplayTags::InitializeNativeGameplayTags();

	// This is required to use Target Data!
	UAbilitySystemGlobals::Get().InitGlobalData();
}
