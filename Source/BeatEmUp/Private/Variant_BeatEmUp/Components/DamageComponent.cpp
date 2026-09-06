// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_BeatEmUp/Components/DamageComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDamageComponent::DealDamage(AActor* TargetActor, float DamageAmount)
{
	if (TargetActor && DamageAmount > 0.0f)
	{
		FDamageEvent DamageEvent;
		
		AController* InstigatorController = nullptr;
		if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
		{
			InstigatorController = OwnerPawn->GetController();
		}
		
		TargetActor->TakeDamage(DamageAmount, DamageEvent, InstigatorController, GetOwner());
	}
}


