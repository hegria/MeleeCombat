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
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MeleeAttributeSet.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "AbilitySystemGlobals.h"

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
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UMeleeAttributeSet>(TEXT("AttributeSet"));
	RotateToTargetTimeLineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("RotateToTargetTimeLineComponent"));
	RotateToTargetTimeLineUpdateDelegate.BindUFunction(this, FName("RotateToTargetUpdate"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	UAbilitySystemGlobals::Get().bUseDebugTargetFromHud = true;

	EquipmentComponent->InitalizeEquipment();
	if (TimelineCurve)
	{
		RotateToTargetTimeLineComponent->AddInterpFloat(TimelineCurve, RotateToTargetTimeLineUpdateDelegate);
		RotateToTargetTimeLineComponent->SetLooping(false);
	}
	StateComponent->OnCharacterActionBegin.BindUFunction(this, FName("OnCharacterActionBegin"));
	StateComponent->OnCharacterActionEnd.BindUFunction(this, FName("OnCharacterActionEnd"));
	StateComponent->OnCharacterStateBegin.BindUFunction(this, FName("OnCharacterStateBegin"));
	StateComponent->OnCharacterStateEnd.BindUFunction(this, FName("OnCharacterStateEnd"));

	InitAbilityActorInfo();
	InitializeDefaultAttributes();
}

void ABaseCharacter::ContinueAttack()
{
	if (CombatComponent->bIsAttackSaved)
	{
		CombatComponent->bIsAttackSaved = false;
		if (StateComponent->GetCurrentState().MatchesTagExact(GET_MELEE_TAG.State_Attacking))
		{
			StateComponent->ResetState();
		}
		Attack();
	}
	else
	{
		CombatComponent->bIsWaitForAttack = true;
	}
}

void ABaseCharacter::ResetCombat()
{
	CombatComponent->ResetAttack();
	StateComponent->ResetState();
	StateComponent->SetCurrentAction(FGameplayTag::EmptyTag);
}


void ABaseCharacter::SetMovable(bool CanMove)
{
	bCanMove = CanMove;
}

void ABaseCharacter::BeginRotateToTarget()
{
	RotateToTargetTimeLineComponent->Play();
}

void ABaseCharacter::StopRotateToTarget()
{
	RotateToTargetTimeLineComponent->Stop();
}

void ABaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	if (CombatComponent->GetMainWeapon().Get())
	{
		// TODO Landed
	}

}

// Called every frame
void ABaseCharacter::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	DeltaTime = _DeltaTime;

	MoveToTargetTimeLine.TickTimeline(_DeltaTime);
	ModifyStamina(StaminaRegenRate * _DeltaTime);
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
	
	return !StateComponent->IsCurrentStateEqualToAny(States) && !GetCharacterMovement()->IsFalling();
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

	return !StateComponent->IsCurrentStateEqualToAny(States) && CombatComponent->IsCombatEnable();

}

bool ABaseCharacter::CanPerformDodge()
{
	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);

	//TODO Stamina

	return !StateComponent->IsCurrentStateEqualToAny(States) &&
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

	return !StateComponent->IsCurrentStateEqualToAny(States) &&
		CombatComponent->IsCombatEnable() && CombatComponent->GetShieldWeapon().Get();
}

bool ABaseCharacter::CanJump()
{
	FGameplayTagContainer States;
	States.AddTag(FMeleeGameplayTags::Get().State_Dodging);
	States.AddTag(FMeleeGameplayTags::Get().State_Dead);
	States.AddTag(FMeleeGameplayTags::Get().State_GeneralActionState);
	States.AddTag(FMeleeGameplayTags::Get().State_Disabled);

	return !StateComponent->IsCurrentStateEqualToAny(States) && !GetCharacterMovement()->IsFalling();
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
	if (CanPerformSprinting())
	{
		ModifyStamina(-2.0);
	}
	else
	{
		DisableSprinting(true);
	}
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
	bIsCharged = ChargeTime >= ChargeAttackTime;
	if (bIsCharged)
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

EHitDirection ABaseCharacter::GetHitDirection(FVector HitLocation)
{
	float Dot = GetActorForwardVector().Dot(
		UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), HitLocation)
	);
	float RightDot = GetActorRightVector().Dot(
		UKismetMathLibrary::GetDirectionUnitVector(GetActorLocation(), HitLocation)
	);
	if (Dot >= 0.3)
	{
		return EHitDirection::EHD_Front;
	}
	if (Dot <= -0.4)
	{
		return EHitDirection::EHD_Back;

	}
	if (RightDot >= 0)
	{
		return EHitDirection::EHD_Right;

	}
	return EHitDirection::EHD_Left;

}

void ABaseCharacter::OnCharacterActionBegin(const FGameplayTag& Action)
{
	if (Action.MatchesTagExact(GET_MELEE_TAG.Action_Dodge))
	{
		if (CombatComponent->GetMainWeapon().Get())
		{
			//Stat Value
		}
	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.Action_EnterBlocking))
	{

	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.Action_ExitBlocking))
	{

	}

}

void ABaseCharacter::OnCharacterActionEnd(const FGameplayTag& Action)
{
	
}

void ABaseCharacter::OnCharacterStateBegin(const FGameplayTag& Action)
{
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Dead))
	{
		TArray<AActor*> ActorsToDestory;
		float Duration;
		PerformDeath(ActorsToDestory, Duration);
		TargetingComponent->DisableLockOn();
		for (auto actor : ActorsToDestory)
		{
			actor->SetLifeSpan(Duration + 4.0);
		}
		SetLifeSpan(Duration + 4.1);
	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Disabled))
	{
		if (!CombatComponent->IsCombatEnable())
		{
			CombatComponent->SetCombatEnable(true);
		}
	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Dodging))
	{
		TargetingComponent->SetRotationMode(ERotationMode::ERM_OrientToMovement);
	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Blocking))
	{
		StopAnimMontage();
		CombatComponent->SetBlockingEnable(true);
		SetMovementSpeedMode(ESpeedMode::ESM_Walking);
		//Stat
	}
}

void ABaseCharacter::OnCharacterStateEnd(const FGameplayTag& Action)
{
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Dodging))
	{
		TargetingComponent->UpdateRotationMode();
	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Blocking))
	{
		CombatComponent->SetBlockingEnable(false);
		SetMovementSpeedMode(ESpeedMode::ESM_Jogging);
	}
	if (Action.MatchesTagExact(GET_MELEE_TAG.State_Attacking))
	{
		StopRotateToTarget();
	}
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

void ABaseCharacter::MoveToTargetupdate(float Output)
{
	SetActorLocation(FMath::Lerp(StartMoveTo, EndMoveTo, Output));
}

void ABaseCharacter::InitializeDefaultAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);

}

void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(AbilitySystemComponent.Get()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
}


void ABaseCharacter::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayTag Tag, float amt)
{
	check(IsValid(AbilitySystemComponent.Get()));
	check(GameplayEffectClass);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	SpecHandle.Data->SetByCallerTagMagnitudes.Add(Tag, amt);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
}

void ABaseCharacter::ModifyStamina(float amt)
{
	ApplyEffectToSelf(UseStaminaEffect, 1, GET_MELEE_TAG.Attributes_Amt_Stamina, amt);
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

void ABaseCharacter::RotateToActor(AActor* Executor)
{
	if (IsValid(Executor))
	{
		SetActorRotation(
			FRotator(
				GetActorRotation().Pitch,
				UKismetMathLibrary::GetDirectionUnitVector(
					GetActorLocation(), Executor->GetActorLocation()).Rotation().Yaw,
				GetActorRotation().Roll
			)
		);
	}
}


void ABaseCharacter::MoveTo(FVector Start, FVector End)
{
	if (TimelineCurve)
	{
		MoveToTargetTimeLineUpdateDelegate.BindUFunction(this, FName("MoveToTargetupdate"));
		MoveToTargetTimeLine.AddInterpFloat(TimelineCurve, MoveToTargetTimeLineUpdateDelegate);
		MoveToTargetTimeLine.PlayFromStart();
	}
}

void ABaseCharacter::ConsumeItem()
{
	CombatComponent->ConsumeItem();
}

bool ABaseCharacter::CanRecieveDamage()
{
	FGameplayTagContainer container = FGameplayTagContainer();
	container.AddTag(GET_MELEE_TAG.State_Dead);
	container.AddTag(GET_MELEE_TAG.State_Dodging);
	return !StateComponent->IsCurrentStateEqualToAny(container);
}

void ABaseCharacter::SetMoveable(bool CanMove)
{
	bCanMove = CanMove;
}

FRotator ABaseCharacter::GetDesireRotation()
{
	if (!GetCharacterMovement()->GetLastInputVector().Equals(FVector::Zero(), 0.001))
	{
		return GetCharacterMovement()->GetLastInputVector().Rotation();
	}
	else
	{
		return GetActorRotation();
	}
}

ESpeedMode ABaseCharacter::GetSpeedMode()
{
	return SpeedMode;
}

void ABaseCharacter::PerformDeath(TArray<AActor*>& ActorToDestory, float& Duration)
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	StateComponent->SetCurrentAction(FMeleeGameplayTags::Get().Action_Die);


	if (CombatComponent->GetMainWeapon().Get())
	{
		CombatComponent->GetMainWeapon()->SimulateWeaponPhysics();
		ActorToDestory.Add(CombatComponent->GetMainWeapon());
		if (!CombatComponent->
			GetMainWeapon()->GetActionMontage(FMeleeGameplayTags::Get().Action_Die).IsEmpty())
		{
			Duration = GetMesh()->GetAnimInstance()->Montage_Play(
				CombatComponent->
				GetMainWeapon()->GetActionMontage(FMeleeGameplayTags::Get().Action_Die)[0],
				1.0,
				EMontagePlayReturnType::Duration
			);

			if (AAIController* AI = UAIBlueprintHelperLibrary::GetAIController(this))
			{
				//AI->GetBrainComponent()->StopLogic(FString("Dead"));

			}

		}
		else
		{
			EnableRagdoll();
			ApplyHitReactionPhysicsVeclocity(250);
		}
	}
	if (CombatComponent->GetShieldWeapon().Get())
	{
		CombatComponent->GetShieldWeapon()->SimulateWeaponPhysics();
		ActorToDestory.Add(CombatComponent->GetShieldWeapon());
	}
	auto equipments = EquipmentComponent->GetCurrentEquipments();
	for (auto equip : equipments)
	{
		ActorToDestory.Add(equip);
	}
}

bool ABaseCharacter::PerformHitReaction(EDamageType DamageType, FVector HitLocation, float Damage)
{
	UAnimMontage* HitMontage = nullptr;
	if (CanBlockAttack() && CombatComponent->GetShieldWeapon().Get())
	{
		float BlockStamina = Damage / -4.0;
		bool StaminaCheck = true;

		if (StaminaCheck)
		{
			StateComponent->SetCurrentState(FMeleeGameplayTags::Get().State_Blocking);
			ModifyStamina(BlockStamina);
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
			ModifyStamina(BlockStamina);
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
			case EDamageType::EDT_None:
				break;
			case EDamageType::EDT_MeleeDamage:
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
			case EDamageType::EDT_KnockdownDamage:
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
			case EDamageType::EDT_None:
				break;
			case EDamageType::EDT_MeleeDamage:
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
			case EDamageType::EDT_KnockdownDamage:
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

bool ABaseCharacter::PerformAction(FGameplayTag CharacterState, FGameplayTag CharacterAction, float MontagePlayRate, int MontageIndex, bool isRandomIndex, float& ActionDuration)
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

bool ABaseCharacter::PerformAttack(FGameplayTag AttackType, int MontageIndex, bool isRandomIndex, bool isCalledbyAI, float PlayRate, float& ActionDuration)
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

				BeginRotateToTarget();

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

void ABaseCharacter::HandlePointDamage(const FHitResult& HitInfo, float Damage, EDamageType DamageType, FVector HitLocation)
{
	if (CanRecieveDamage())
	{

		if (AttributeSet->GetHealth() == 0)
		{
			StateComponent->SetCurrentState(GET_MELEE_TAG.State_Dead);
			return;
		}
		HitDirection = GetHitDirection(HitLocation);
		PerformHitReaction(DamageType, HitLocation, Damage);

	}
}

