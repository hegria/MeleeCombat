// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/MeleePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Input/MeleeInputComponent.h"
#include "Character/BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Component/TargetComponent.h"
#include "Component/CombatComponent.h"
#include "Component/StateComponent.h"
#include "MeleeGameplayTags.h"
#include "InputActionValue.h"
#include "Components/WidgetComponent.h"
#include "UI/Widget/MainHUD.h"

void AMeleePlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
		Subsystem->AddMappingContext(MeleeContext, 0);

	PlayerCharacter = Cast<ABaseCharacter>(GetCharacter());

	HUD = CreateWidget<UMainHUD>(GetWorld(), MainHUDClass);

	HUD->AddToViewport();
}



void AMeleePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UMeleeInputComponent* MeleeInputComponent = CastChecked<UMeleeInputComponent>(InputComponent);
	MeleeInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMeleePlayerController::Move);
	MeleeInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMeleePlayerController::Look);
	MeleeInputComponent->BindAction(LightClickAction, ETriggerEvent::Triggered, this, &AMeleePlayerController::LightAttackTriggered);
	MeleeInputComponent->BindAction(LightClickAction, ETriggerEvent::Started, this, &AMeleePlayerController::LightAttackStarted);
	MeleeInputComponent->BindAbilityActions(InputConfig, this,
		&ThisClass::AbilityInputTagStarted,
		&ThisClass::AbilityInputTagCompleted,
		&ThisClass::AbilityInputTagTriggered);
}

void AMeleePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AMeleePlayerController::InitHUD()
{
	HUD->Init(PlayerCharacter->AbilitySystemComponent, PlayerCharacter->AttributeSet.Get());

}

void AMeleePlayerController::Move(const FInputActionValue& value)
{
	const FVector2D InputVector = value.Get<FVector2D>();
	if (PlayerCharacter->bCanMove)
	{
		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetRightVector(FRotator(
				0,
				GetControlRotation().Yaw,
				GetControlRotation().Roll
			)),
			InputVector.X
		);
		PlayerCharacter->AddMovementInput(
			UKismetMathLibrary::GetForwardVector(FRotator(
				0,
				GetControlRotation().Yaw,
				0
			)),
			InputVector.Y
		);
	}
}

void AMeleePlayerController::Look(const FInputActionValue& value)
{
	const FVector2D InputVector = value.Get<FVector2D>();

	float YVal = InputVector.Y;

	if (PlayerCharacter->TargetingComponent->IsTargeting())
	{
		YVal *= 0.2;
	}
	else
	{
		AddYawInput(InputVector.X);
	}

	AddPitchInput(YVal);
}

void AMeleePlayerController::JumpTriggered()
{
	if (PlayerCharacter->CanJump())
	{
		PlayerCharacter->StopAnimMontage();
		PlayerCharacter->StateComponent->ResetState();
		PlayerCharacter->CombatComponent->ResetAttack();
		PlayerCharacter->Jump();
	}
}

void AMeleePlayerController::JumpCompleted()
{
	PlayerCharacter->StopJumping();
}

void AMeleePlayerController::ToggleCombatCompleted()
{
	if (PlayerCharacter->CanPerformToggleCombat())
	{
		if (PlayerCharacter->CombatComponent->GetMainWeapon().Get())
		{
			float Duration;
			if (PlayerCharacter->CombatComponent->IsCombatEnable())
			{
				PlayerCharacter->PerformAction(
					GET_MELEE_TAG.State_GeneralActionState,
					GET_MELEE_TAG.Action_ExitCombat,
					1.0,
					0,
					false,
					Duration
					);
			}
			else
			{
				PlayerCharacter->PerformAction(
					GET_MELEE_TAG.State_GeneralActionState,
					GET_MELEE_TAG.Action_EnterCombat,
					1.0,
					0,
					false,
					Duration
				);
			}
		}
		else
		{
			PlayerCharacter->StateComponent->ResetState();
		}
	}
}

void AMeleePlayerController::InteractStarted()
{
	FHitResult OnHit;
	TArray<AActor*> IgnoreActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TEnumAsByte<EObjectTypeQuery> InterActable = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_EngineTraceChannel1);
	ObjectTypes.Add(InterActable);
	bool isHit = UKismetSystemLibrary::SphereTraceSingleForObjects(this,
		PlayerCharacter->GetActorLocation(),
		PlayerCharacter->GetActorLocation(),
		100,
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		OnHit,
		true
	);
	if (isHit)
	{
		//Interactable
	}
}

void AMeleePlayerController::LightAttackTriggered(const struct FInputActionInstance& instance)
{
	PlayerCharacter->ChargeAttacktimer(instance.GetElapsedTime());
}

void AMeleePlayerController::LightAttackStarted(const struct FInputActionInstance& instance)
{
	if (PlayerCharacter->ResetChargeAttack())
	{
		PlayerCharacter->bIsHeavyAttack = false;
		if (PlayerCharacter->StateComponent->GetCurrentState().MatchesTagExact(GET_MELEE_TAG.State_Attacking))
		{
			if (PlayerCharacter->CombatComponent->bIsWaitForAttack)
			{
				PlayerCharacter->CombatComponent->bIsWaitForAttack = false;
				PlayerCharacter->StateComponent->ResetState();
				PlayerCharacter->Attack();
			}
			else
			{
				PlayerCharacter->CombatComponent->bIsAttackSaved = true;
			}
		}
		else
		{
			PlayerCharacter->Attack();
		}
	}
}

void AMeleePlayerController::DodgeStarted()
{
	if (PlayerCharacter->CanPerformDodge())
	{
		float Duration;
		PlayerCharacter->PerformAction(
			GET_MELEE_TAG.State_Dodging,
			GET_MELEE_TAG.Action_Dodge,
			1.0,
			0,
			false,
			Duration
		);
	}

}

void AMeleePlayerController::ToggleWalkStarted()
{
	if (PlayerCharacter->GetMovementSpeedMode() == ESpeedMode::ESM_Walking)
	{
		PlayerCharacter->SetMovementSpeedMode(ESpeedMode::ESM_Jogging);
	}
	else
	{
		PlayerCharacter->SetMovementSpeedMode(ESpeedMode::ESM_Walking);
	}
}

void AMeleePlayerController::SprintTriggered()
{
	if (PlayerCharacter->CanPerformSprinting())
	{
		PlayerCharacter->SetMovementSpeedMode(ESpeedMode::ESM_Sprinting);
		if (PlayerCharacter->SprintingTimer())
		{
			PlayerCharacter->SprintingStaminaCost();
		}
	}
	else
	{
		PlayerCharacter->DisableSprinting(true);
	}
}

void AMeleePlayerController::SprintCompleted()
{
	PlayerCharacter->DisableSprinting(false);
}

void AMeleePlayerController::HeavyAttackCompleted()
{
	PlayerCharacter->bIsHeavyAttack = true;
	if (PlayerCharacter->StateComponent->GetCurrentState().MatchesTagExact(GET_MELEE_TAG.State_Attacking))
	{
		PlayerCharacter->CombatComponent->bIsAttackSaved = true;
	}
	else
	{
		PlayerCharacter->Attack();
	}
}

void AMeleePlayerController::ToggleLockStarted()
{
	PlayerCharacter->TargetingComponent->ToggleLockOn();
}

void AMeleePlayerController::BlockStarted()
{
	if (PlayerCharacter->CanPerformBlock())
	{
		PlayerCharacter->ResetCombat();
		PlayerCharacter->StateComponent->SetCurrentState(GET_MELEE_TAG.State_Blocking);
		PlayerCharacter->StateComponent->SetCurrentAction(GET_MELEE_TAG.Action_EnterBlocking);
	}
}

void AMeleePlayerController::BlockCompleted()
{
	PlayerCharacter->StateComponent->ResetState();
	PlayerCharacter->StateComponent->SetCurrentAction(GET_MELEE_TAG.Action_ExitBlocking);
}

void AMeleePlayerController::UseItemStarted()
{
	float Duration;
	PlayerCharacter->PerformUseItem(
		GET_MELEE_TAG.State_GeneralActionState,
		GET_MELEE_TAG.Action_UseItem,
		1.0,
		0,
		false,
		Duration
	);
}

void AMeleePlayerController::AbilityInputTagStarted(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Interact))
	{
		InteractStarted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Dodge))
	{
		DodgeStarted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_ToggleWalk))
	{
		ToggleWalkStarted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_ToggleLock))
	{
		ToggleLockStarted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Block))
	{
		BlockStarted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_UseItem))
	{
		UseItemStarted();
	}
}

void AMeleePlayerController::AbilityInputTagCompleted(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Jump))
	{
		JumpCompleted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_ToggleCombat))
	{
		ToggleCombatCompleted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Sprint))
	{
		SprintCompleted();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Block))
	{
		BlockCompleted();
	}
}

void AMeleePlayerController::AbilityInputTagTriggered(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Jump))
	{
		JumpTriggered();
	}
	if (InputTag.MatchesTagExact(GET_MELEE_TAG.InputTag_Sprint))
	{
		SprintTriggered();
	}
}
