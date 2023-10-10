// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MeleeAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MELEECOMBAT_API UMeleeAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UMeleeAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
