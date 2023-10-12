// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TargetingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTargetingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MELEECOMBAT_API ITargetingInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanbeTargeted() = 0;
	virtual void EnableLockOn(bool EnableLockon) = 0;
	virtual void OnTargeted(bool IsTargeted) = 0;
	
};
