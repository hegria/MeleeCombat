// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/TargetComponent.h"
#include "Component/CombatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/TargetingInterface.h"
#include "Interface/CombatInterface.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UTargetComponent::UTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OwnerCharacter = Cast<ACharacter>(GetOwner());
	OwnerController = OwnerCharacter->GetController();

	FollowCamera = OwnerCharacter->GetComponentByClass<UCameraComponent>();
	OwnerCombatComponent = OwnerCharacter->GetComponentByClass<UCombatComponent>();
	// ...
}


// Called every frame
void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (bIsTargeting)
	{
		UpdateTargetingControlRotation();
	}
}

void UTargetComponent::SetIsTargeting(bool IsTargeting)
{
	bIsTargeting = IsTargeting;

	if (TargetActor.Get())
	{
		Cast<ITargetingInterface>(TargetActor.Get())->OnTargeted(IsTargeting);
	}
}

bool UTargetComponent::FindTarget(OUT AActor* Result)
{

	FHitResult OnHit;

	bool isHit = UKismetSystemLibrary::SphereTraceSingleForObjects(this,
		GetOwner()->GetActorLocation() ,
		GetOwner()->GetActorLocation() +
		TargetingDistance * FollowCamera->GetForwardVector().RotateAngleAxis(-15, FollowCamera->GetRightVector()),
		TargetingRadius,
		TargetObjectType,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OnHit,
		true
	);
	if (isHit && IsValid(OnHit.GetActor()) && Cast<ITargetingInterface>(OnHit.GetActor()))
	{
		Result = OnHit.GetActor();
		return true;
	}

	return false;
}

void UTargetComponent::SetTargetActor(AActor* NewTargetActor)
{
	TargetActor = NewTargetActor;
}

void UTargetComponent::UpdateTargetingControlRotation()
{
	if (IsValid(TargetActor) && IsValid(OwnerController))
	{
		if (CanTargetActor(TargetActor))
		{
			const FRotator ControllerRotation = OwnerController->GetControlRotation();


			FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(
				GetOwner()->GetActorLocation(),
				TargetActor->GetActorLocation() - 120 * FVector::UpVector
			);

			FRotator NewRotation = FRotator(ControllerRotation.Pitch,
				FMath::RInterpTo(
					ControllerRotation,
					LookRotation,
					GetWorld()->DeltaTimeSeconds,
					TargetRotationInterpSpeed
				).Yaw
				, ControllerRotation.Roll);
			OwnerController->SetControlRotation(NewRotation);

			return;
		}
	}
	
	DisableLockOn();
}

bool UTargetComponent::CanTargetActor(AActor* InTargetActor)
{
	return Cast<ITargetingInterface>(InTargetActor)->CanbeTargeted()
		&& GetOwner()->GetDistanceTo(InTargetActor) < TargetingDistance;
}

void UTargetComponent::SetRotationMode(ERotationMode NewRotationMode)
{
	CurrentRotationMode = NewRotationMode;
	switch (CurrentRotationMode)
	{
	case ERotationMode::ERM_OrientToCamera:
		OwnerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;
		break;
	case ERotationMode::ERM_OrientToMovement:
		OwnerCharacter->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	default:
		break;
	}
}

void UTargetComponent::UpdateRotationMode()
{

	ERotationMode mode = ERotationMode::ERM_OrientToMovement;

	if (OwnerCombatComponent.Get())
	{
		if (Cast<ICombatInterface>(OwnerCharacter)->GetSpeedMode() != ESpeedMode::ESM_Sprinting
			&& OwnerCombatComponent->IsCombatEnable()
			&& bIsTargeting)
			mode = ERotationMode::ERM_OrientToCamera;
	}

	SetRotationMode(mode);
}

void UTargetComponent::EnableLockOn(bool CalledByAI)
{
	if (CalledByAI)
	{
		if (CanTargetActor(GetWorld()->GetFirstPlayerController()->GetCharacter()))
		{
			SetTargetActor(GetWorld()->GetFirstPlayerController()->GetCharacter());
			SetIsTargeting(true);
			UpdateRotationMode();
		}
		else
		{
			DisableLockOn();
		}
	}
	else if (OwnerCombatComponent->IsCombatEnable())
	{
		AActor* result = nullptr;
		if (FindTarget(result) && CanTargetActor(result))
		{
			SetTargetActor(result);
			SetIsTargeting(true);
			UpdateRotationMode();
		}
	}
}

void UTargetComponent::DisableLockOn()
{
	SetIsTargeting(false);
	SetTargetActor(nullptr);
	UpdateRotationMode();

	// TODO AI한테 알리기 ㅅㅂ;
}

void UTargetComponent::ToggleLockOn()
{
	if (IsTargeting())
	{
		DisableLockOn();
	}
	else
	{
		EnableLockOn(false);
	}
}

