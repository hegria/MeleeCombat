// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"


class ABaseEquippable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MELEECOMBAT_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitalizeEquipment();
	FORCEINLINE TArray<ABaseEquippable*> GetCurrentEquipments() { return CurrentEquipments;	}
	
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ABaseEquippable>> StartingEquipments;
	UPROPERTY()
	TArray<ABaseEquippable*> CurrentEquipments;
		
};
