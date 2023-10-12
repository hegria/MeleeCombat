// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/CombatComponent.h"
#include "Component/StateComponent.h"
#include "Component/EquipmentComponent.h"
#include "Component/TargetComponent.h"
#include "Components/CapsuleComponent.h"
#include "Actor/Weapon/BaseWeapon.h"
#include "Actor/Weapon/BaseConsumeable.h"
#include "MeleeGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 400.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
	StateComponent = CreateDefaultSubobject<UStateComponent>(TEXT("StateComponent"));
	TargetingComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetingComponent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	RotateToTargetTimeLineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("RotateToTargetTimeLineComponent"));
	RotateToTargetTimeLineUpdateDelegate.BindUFunction(this, FName("RotateToTargetUpdate"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipmentComponent->InitalizeEquipment();
	if (TimelineCurve)
	{
		RotateToTargetTimeLineComponent->AddInterpFloat(TimelineCurve, RotateToTargetTimeLineUpdateDelegate);
		RotateToTargetTimeLineComponent->SetLooping(false);

	}
}

void ABaseCharacter::ContinueAttack()
{

}

void ABaseCharacter::ResetCombat()
{
}

void ABaseCharacter::PointDamage()
{

}

// Called every frame
void ABaseCharacter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DeltaTime = _DeltaTime;

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = OwnedGameplayTags;
}

bool ABaseCharacter::CanPerformToggleCombat()
{
	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Attacking);
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);
	
	return !StateComponent->IsCurrentActionEqualToAny(States) && !GetCharacterMovement()->IsFalling();
}

bool ABaseCharacter::CanPerformAttack()
{
	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Attacking);
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);
	States.AddTag(FMeleeGameplayTags::Get().State_Blocking);


	//TODO Stamina

	return !StateComponent->IsCurrentActionEqualToAny(States) && CombatComponent->IsCombatEnable();

}

bool ABaseCharacter::CanPerformDodge()
{
	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);

	//TODO Stamina

	return !StateComponent->IsCurrentActionEqualToAny(States) &&
		!(GetCharacterMovement()->IsFalling() || !CombatComponent->IsCombatEnable());
}

bool ABaseCharacter::CanPerformSprinting()
{
	//TODO Stamina

	return GetVelocity().Length() >= 10 && !bIsForceExitSprinting;
}

bool ABaseCharacter::CanPerformBlock()
{
	

	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);
	States.AddTag(FMeleeGameplayTags::Get().State_Blocking);

	//TODO Stamina

	return !StateComponent->IsCurrentActionEqualToAny(States) &&
		CombatComponent->IsCombatEnable() && CombatComponent->GetShieldWeapon().Get();
}

bool ABaseCharacter::CanJump()
{
	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);

	return !StateComponent->IsCurrentActionEqualToAny(States) && !GetCharacterMovement()->IsFalling();
}

bool ABaseCharacter::CanBlockAttack()
{
	return CombatComponent->IsBlockingEnable()&&HitDirection != EHitDirection::EHD_Back;
}

void ABaseCharacter::SetMovementSpeedMode(ESpeedMode NewSpeedMode)
{
	if (NewSpeedMode == SpeedMode) return;
	SpeedMode = NewSpeedMode;
	TargetingComponent->UpdateRotationMode();
	switch (SpeedMode)
	{
	case ESpeedMode::ESM_Walking:
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkingSpeed;
		break;
	case ESpeedMode::ESM_Jogging:
		GetCharacterMovement()->MaxWalkSpeed = MaxJogginSepeed;
		break;
	case ESpeedMode::ESM_Sprinting:
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintingSpeed;
		break;
	default:
		break;
	}
}

FGameplayTag ABaseCharacter::GetDesiredAttackType()
{
	if (GetCharacterMovement()->IsFalling())
	{
		return FMeleeGameplayTags::Get().Action_Attack_FallingAttack;
	}
	if (GetMovementSpeedMode() == ESpeedMode::ESM_Sprinting)
	{
		return FMeleeGameplayTags::Get().Action_Attack_SprintAttack;
	}
	if (bIsHeavyAttack)
	{
		return FMeleeGameplayTags::Get().Action_Attack_HeavyAttack;
	}

	return FMeleeGameplayTags::Get().Action_Attack_LightAttack;
}

void ABaseCharacter::Attack()
{
	if (!CanPerformAttack()) return;

	float AttactDuration;

	PerformAttack(
		GetDesiredAttackType(), CombatComponent->AttackCount,
		false,
		false,
		1.0, AttactDuration);
	if (CombatComponent->GetMainWeapon().Get())
	{
		// TODO Stamina
	}
}

void ABaseCharacter::ChargeAttack()
{
	if (!CanPerformAttack()) return;
	float AttactDuration;

	PerformAttack(
		FMeleeGameplayTags::Get().Action_Attack_ChargedAttack,
		CombatComponent->AttackCount,
		false,
		false,
		1.0, AttactDuration);

	if (CombatComponent->GetMainWeapon().Get())
	{
		// TODO Stamina
	}
}

bool ABaseCharacter::ResetChargeAttack()
{
	ChargeTime = 0;
	if (bIsCharged)
	{
		bIsCharged = false;
		return false;
	}
	else
	{
		return true;
	}
}

void ABaseCharacter::SprintingStaminaCost()
{
	//TODO Sptrint
}

bool ABaseCharacter::SprintingTimer()
{
	SprintingInputDeltaTime += DeltaTime;

	if (SprintingInputDeltaTime > 0.1)
	{
		SprintingInputDeltaTime = 0;
		return true;
	}
	return false;
}

void ABaseCharacter::DisableSprinting(bool IsForceExitSprinting)
{
	bIsForceExitSprinting = IsForceExitSprinting;

	if (GetMovementSpeedMode() == ESpeedMode::ESM_Sprinting)
	{
		SetMovementSpeedMode(ESpeedMode::ESM_Jogging);
	}
}

void ABaseCharacter::ChargeAttacktimer(float PressTime)
{
	ChargeTime = PressTime;
	if (bIsCharged = ChargeTime >= ChargeAttackTime)
	{
		ChargeAttack();
	}
}

void ABaseCharacter::EnableRagdoll()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	FAttachmentTransformRules rule = FAttachmentTransformRules(
		EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);

	CameraBoom->AttachToComponent(GetMesh(), rule, PelvisBoneName);
	CameraBoom->bDoCollisionTest = false;
	GetMesh()->SetCollisionProfileName(FName("Ragdoll"));
	GetMesh()->SetAllBodiesBelowSimulatePhysics(PelvisBoneName, true);
	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(PelvisBoneName, 1.0);
}

void ABaseCharacter::ApplyHitReactionPhysicsVeclocity(float InitialSpeed)
{
	GetMesh()->SetPhysicsLinearVelocity(
		-InitialSpeed * GetActorForwardVector(),false , PelvisBoneName
	);
}

void ABaseCharacter::RotateToTargetUpdate(float Output)
{
	if (TargetingComponent->GetTargetActor().Get())
	{
		FRotator LookRotation = UKismetMathLibrary::FindLookAtRotation(
			GetActorLocation(),
			TargetingComponent->GetTargetActor()->GetActorLocation()
		);

		SetActorRotation(
			FRotator(
				GetActorRotation().Pitch,
				FMath::RInterpTo(
					GetActorRotation(),
					LookRotation,
					GetWorld()->DeltaTimeSeconds,
					9.0
				).Yaw
				,
				GetActorRotation().Roll
			)
		);
	}
}

bool ABaseCharacter::CanbeTargeted()
{
	FGameplayTagContainer tags = FGameplayTagContainer(FMeleeGameplayTags::Get().State_Dead);
	return !StateComponent->IsCurrentStateEqualToAny(tags);
}

void ABaseCharacter::EnableLockOn(bool isEnableLockon)
{
	if (isEnableLockon)
	{
		TargetingComponent->UpdateRotationMode();
	}
	else
	{
		TargetingComponent->SetRotationMode(ERotationMode::ERM_OrientToMovement);
	}
}

void ABaseCharacter::OnTargeted(bool IsTargeted)
{
	
}

void ABaseCharacter::RotateToActor(AActor* Excutor)
{
	
}

void ABaseCharacter::JumpTo(float FlightTime)
{
}

void ABaseCharacter::MoveTo(FVector Start, FVector End)
{
}

void ABaseCharacter::ConsumeItem()
{
}

bool ABaseCharacter::CanRecieveDamage()
{
	return false;
}

void ABaseCharacter::SetMoveable(bool CanMove)
{
}

FRotator ABaseCharacter::GetDesireRotation()
{
	return FRotator();
}

ESpeedMode ABaseCharacter::GetSpeedMode()
{
	return ESpeedMode();
}

void ABaseCharacter::PerformDeath(TArray<AActor*>& ActorToDestory, float& Duration)
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	StateComponent->SetCurrentAction(FMeleeGameplayTags::Get().Action_Die);

	TArray<AActor*> DestoryActorsArray;
	float AnimDuration;

	if (CombatComponent->GetMainWeapon().Get())
	{
		CombatComponent->GetMainWeapon()->SimulateWeaponPhysics();
		DestoryActorsArray.Add(CombatComponent->GetMainWeapon());
		if (!CombatComponent->
			GetMainWeapon()->GetActionMontage(FMeleeGameplayTags::Get().Action_Die).IsEmpty())
		{
			AnimDuration = GetMesh()->GetAnimInstance()->Montage_Play(
				CombatComponent->
				GetMainWeapon()->GetActionMontage(FMeleeGameplayTags::Get().Action_Die)[0],
				1.0,
				EMontagePlayReturnType::Duration
			);

		}
		else
		{
			EnableRagdoll();
			ApplyHitReactionPhysicsVeclocity(250);
		}
	}
	
}

bool ABaseCharacter::PerformHitReaction(EDamegeType DamageType, FVector HitLocation, float Damage)
{
	UAnimMontage* HitMontage = nullptr;
	if (CanBlockAttack() && CombatComponent->GetShieldWeapon().Get())
	{
		float BlockStamina = Damage / -4.0;
		bool StaminaCheck = true;

		if (StaminaCheck)
		{
			StateComponent->SetCurrentState(FMeleeGameplayTags::Get().State_Blocking);
			// TODO Minus Blocking
			HitMontage = CombatComponent->GetShieldWeapon()->DefenseHitMontage;

			GetMesh()->GetAnimInstance()->Montage_Play(
				HitMontage,
				1.0,
				EMontagePlayReturnType::Duration
			);

			// TODO Play Block Sound


			return false;
		}
		else
		{
			StateComponent->SetCurrentState(FMeleeGameplayTags::Get().State_Disabled);
			// TODO Minus Blocking
			HitMontage = CombatComponent->GetShieldWeapon()->DefenseHitBrokenMontage;
		}
	}
	else
	{
		StateComponent->SetCurrentState(FMeleeGameplayTags::Get().State_Disabled);
		if (CombatComponent->GetMainWeapon().Get())
		{
			switch (DamageType)
			{
			case EDamegeType::EDT_None:
				break;
			case EDamegeType::EDT_MeleeDamage:
			{
				switch (HitDirection)
				{
				case EHitDirection::EHD_Front:
					HitMontage = CombatComponent->GetMainWeapon()->HitMontage_F;
					break;
				case EHitDirection::EHD_Back:
					HitMontage = CombatComponent->GetMainWeapon()->HitMontage_B;
					break;
				case EHitDirection::EHD_Left:
					HitMontage = CombatComponent->GetMainWeapon()->HitMontage_L;
					break;
				case EHitDirection::EHD_Right:
					HitMontage = CombatComponent->GetMainWeapon()->HitMontage_R;
					break;
				default:
					break;
				}
			}
			break;
			case EDamegeType::EDT_KnockdownDamage:
			{
				switch (HitDirection)
				{
				case EHitDirection::EHD_Front:
					HitMontage = CombatComponent->GetMainWeapon()->KnockdownMontage_F;
					break;
				case EHitDirection::EHD_Back:
					HitMontage = CombatComponent->GetMainWeapon()->KnockdownMontage_B;
					break;
				case EHitDirection::EHD_Left:
					HitMontage = CombatComponent->GetMainWeapon()->KnockdownMontage_F;
					break;
				case EHitDirection::EHD_Right:
					HitMontage = CombatComponent->GetMainWeapon()->KnockdownMontage_F;
					break;
				default:
					break;
				}
			}
			break;
			default:
				break;
			}
		}
		else
		{
			
			switch (DamageType)
			{
			case EDamegeType::EDT_None:
				break;
			case EDamegeType::EDT_MeleeDamage:
				{
				switch (HitDirection)
				{
					case EHitDirection::EHD_Front:
						HitMontage = UnarmHitMontage_F;
						break;
					case EHitDirection::EHD_Back:
						HitMontage = UnarmHitMontage_B;
						break;
					case EHitDirection::EHD_Left:
						HitMontage = UnarmHitMontage_L;
						break;
					case EHitDirection::EHD_Right:
						HitMontage = UnarmHitMontage_R;
						break;
					default:
						break;
					}
				}
				break;
			case EDamegeType::EDT_KnockdownDamage:
			{
				switch (HitDirection)
				{
				case EHitDirection::EHD_Front:
					HitMontage = KnockdownMontage_F;
					break;
				case EHitDirection::EHD_Back:
					HitMontage = KnockdownMontage_B;
					break;
				case EHitDirection::EHD_Left:
					HitMontage = KnockdownMontage_F;
					break;
				case EHitDirection::EHD_Right:
					HitMontage = KnockdownMontage_F;
					break;
				default:
					break;
				}
			}
				break;
			default:
				break;
			}
			
		}
	}
	if (IsValid(HitMontage))
	{
		GetMesh()->GetAnimInstance()->Montage_Play(
			HitMontage,
			1.0,
			EMontagePlayReturnType::Duration
		);
		return true;
	}
	return false;
}

bool ABaseCharacter::PerformUseItem(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, OUT float& ActionDuration)
{
	if (CombatComponent->GetItem().Get())
	{
		auto Montages = CombatComponent->GetItem()->GetUseItemMontages();
		if (Montages.IsValidIndex(MontageIndex))
		{
			UAnimMontage* ActionMontage;
			if (isRandomIndex)
			{
				ActionMontage = Montages[FMath::RandRange(0, Montages.Num() - 1)];
			}
			else
			{
				ActionMontage = Montages[MontageIndex];

			}
			if (IsValid(ActionMontage))
			{
				StateComponent->SetCurrentState(CharacterState);
				StateComponent->SetCurrentAction(CharacterAction);
				//TODO BeginRoatate To Target
				ActionDuration = GetMesh()->GetAnimInstance()->Montage_Play(
					ActionMontage,
					MontagePlayRate,
					EMontagePlayReturnType::Duration
				);
				return true;
			}
		}
	}
	return false;
}

bool ABaseCharacter::PerformAction(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, OUT float& ActionDuration)
{
	if (CombatComponent->GetMainWeapon().Get())
	{
		auto Montages = CombatComponent->GetMainWeapon()->GetActionMontage(CharacterAction);
		if (Montages.IsValidIndex(MontageIndex))
		{
			UAnimMontage* ActionMontage;
			if (isRandomIndex)
			{
				ActionMontage = Montages[FMath::RandRange(0, Montages.Num() - 1)];
			}
			else
			{
				ActionMontage = Montages[MontageIndex];

			}
			if (IsValid(ActionMontage))
			{
				StateComponent->SetCurrentState(CharacterState);
				StateComponent->SetCurrentAction(CharacterAction);
				//TODO BeginRoatate To Target
				ActionDuration = GetMesh()->GetAnimInstance()->Montage_Play(
					ActionMontage,
					MontagePlayRate,
					EMontagePlayReturnType::Duration
				);
				return true;
			}
		}
	}

	return false;
}

bool ABaseCharacter::PerformAttack(FGameplayTag AttackType, int MontageIndex, bool isRandomIndex, bool isCalledbyAI, float PlayRate, OUT float& ActionDuration)
{
	if (isCalledbyAI)
	{
		if (Cast<ITargetingInterface>(UGameplayStatics::GetPlayerPawn(this,0))->CanbeTargeted())
		{
			TargetingComponent->EnableLockOn(true);
		}
		else
		{
			TargetingComponent->DisableLockOn();
			return false;
		}
	}
	if (TargetingComponent->GetTargetActor().Get())
	{
		// 참수 (걍안할거임)
	}
	if (CombatComponent->GetMainWeapon().Get())
	{
		auto Montages = CombatComponent->GetMainWeapon()->GetActionMontage(AttackType);
		if (Montages.IsValidIndex(MontageIndex))
		{
			UAnimMontage* AttackMontage;
			if (isRandomIndex)
			{
				AttackMontage = Montages[FMath::RandRange(0, Montages.Num() - 1)];
			}
			else
			{
				AttackMontage = Montages[MontageIndex];

			}
			if (IsValid(AttackMontage))
			{
				StateComponent->SetCurrentState(FMeleeGameplayTags::Get().State_Attacking);
				StateComponent->SetCurrentAction(AttackType);
				//TODO BeginRoatate To Target
				ActionDuration = GetMesh()->GetAnimInstance()->Montage_Play(
					AttackMontage,
					PlayRate,
					EMontagePlayReturnType::Duration
				);
				CombatComponent->AttackCount++;
				if (CombatComponent->AttackCount > Montages.Num() - 1)
				{
					CombatComponent->AttackCount = 0;
				}
				return true;
			}
		}
	}
	return false;
}

