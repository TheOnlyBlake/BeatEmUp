// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_BeatEmUp/Components/HealthComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/Engine.h"

#include "VectorUtil.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	}
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageAmount <= 0.0f || CurrentHealth <= 0.0f) return;
	
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Damage: %f | Damaged Actor %s"), DamageAmount, *DamagedActor->GetName()));
	
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	
	if (CurrentHealth == 0.0f)
	{
		OnHealthDepleted.Broadcast();
	}
}

void UHealthComponent::Heal(float HealAmount)
{
	if (CurrentHealth < MaxHealth)
	{
		CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	}
}

float UHealthComponent::GetHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}





