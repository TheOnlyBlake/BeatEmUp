// Copyright Epic Games, Inc. All Rights Reserved.

#include "BeatEmUpCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "CollisionQueryParams.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "BeatEmUp.h"

ABeatEmUpCharacter::ABeatEmUpCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// configure the Pawn properties
	bUseControllerRotationYaw = false;
	

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// create the camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	
	Camera->SetRelativeLocationAndRotation(FVector(0.0f, 300.0f, 0.0f), FRotator(0.0f, -90.0f, 0.0f));
	
	// create the health and damage components
	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("Damage Component"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ABeatEmUpCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABeatEmUpCharacter::Move);
		
		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ABeatEmUpCharacter::Attack);
	}
	else
	{
		UE_LOG(LogBeatEmUp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABeatEmUpCharacter::Move(const FInputActionValue& Value)
{
	
	// input is a Vector2D
	FVector2D MoveVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MoveVector.Y);
}

void ABeatEmUpCharacter::Attack(const FInputActionValue& Value)
{
	DoAttack();
}

void ABeatEmUpCharacter::DoMove(float Forward)
{
	if (GetController() != nullptr)
	{
		ActionValueY = Forward;
		
		const FVector MoveDir = FVector(1.0f, Forward > 0.0f ? 0.1f : -0.1f, 0.0f);
		
		// add movement 
		AddMovementInput(MoveDir, Forward);
	}
}


void ABeatEmUpCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ABeatEmUpCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ABeatEmUpCharacter::DoAttack()
{
	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Warning, TEXT("AttackMontage is null! Please assign it in the Blueprint instance."));
		return;
	}
	
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	
	if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		float PlayLength = AnimInstance->Montage_Play(AttackMontage, 1.25f);
	}
	
	UWorld* World = GetWorld();
	if (!World) return;
	
	FVector StartLocation = GetActorLocation() + (GetActorForwardVector() * 40.0f);
	FVector EndLocation = StartLocation + (GetActorForwardVector() * AttackRange);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(AttackRadius);
	
	FHitResult HitResult;
	bool bHit = World->SweepSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_Pawn,
		SphereShape,
		QueryParams
	);
	
	if (bShowDebugTrace)
	{
		FColor TraceColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(World, StartLocation, EndLocation, TraceColor, false, 2.0f, 0, 2.0f);
		FVector DebugSphereLocation = bHit ? HitResult.ImpactPoint : EndLocation;
		DrawDebugSphere(World, DebugSphereLocation, AttackRadius, 12, TraceColor, false, 2.0f);
	}
	
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			//Damage Logic
			DamageComponent->DealDamage(HitActor, Damage);
		}
	}
}
