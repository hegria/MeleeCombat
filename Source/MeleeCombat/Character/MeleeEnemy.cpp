// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MeleeEnemy.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/EnemyHealthBar.h"
#include "Components/WidgetComponent.h"

AMeleeEnemy::AMeleeEnemy()
{
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("HealthBarWidgetComponent"));
	LockOnWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("LockOnWidgetComponent"));
	HealthBarWidgetComponent->SetupAttachment(GetMesh());
	LockOnWidgetComponent->SetupAttachment(GetMesh());
}

void AMeleeEnemy::BeginPlay()
{
	Super::BeginPlay();
	UEnemyHealthBar* HealthBar = CreateWidget<UEnemyHealthBar>(GetWorld(), HealthBarWidget);
	UUserWidget* LockOn = CreateWidget(GetWorld(), LockOnWidget);
	HealthBar->Init(AbilitySystemComponent, AttributeSet.Get());
	HealthBarWidgetComponent->SetWidget(HealthBar);
	HealthBarWidgetComponent->SetVisibility(false);
	LockOnWidgetComponent->SetWidget(LockOn);
	LockOnWidgetComponent->SetVisibility(false);

}

void AMeleeEnemy::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (LockOnWidgetComponent->IsVisible())
	{
		LockOnWidgetComponent->SetWorldLocation(
			GetMesh()->GetCenterOfMass(FName("pelvis")) + FVector::UpVector * 50);
	}
}

void AMeleeEnemy::InitAbilityActorInfo()
{

}

void AMeleeEnemy::OnTargeted(bool IsTargeted)
{
	LockOnWidgetComponent->SetVisibility(IsTargeted);
	HealthBarWidgetComponent->SetVisibility(IsTargeted);
}
