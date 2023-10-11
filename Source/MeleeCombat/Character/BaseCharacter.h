// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterStates.h"
#include "GameplayTagAssetInterface.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MELEECOMBAT_API ABaseCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UPROPERTY()
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY()
	TObjectPtr<UCameraComponent> ViewCamera;

	FGameplayTagContainer OwnedGameplayTagContainer;

	// Inherited via IGameplayTagAssetInterface
};
