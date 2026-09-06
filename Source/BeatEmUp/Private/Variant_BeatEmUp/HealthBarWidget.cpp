// Fill out your copyright notice in the Description page of Project Settings.


#include "Variant_BeatEmUp/HealthBarWidget.h"

#include "Variant_BeatEmUp/Components/HealthComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::OnHealthChanged(float NewHealth, float MaxHealth)
{
	float HealthPercent = NewHealth / MaxHealth;
	HealthProgressBar->SetPercent(HealthPercent);
	HealthTextBlock->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), static_cast<int32>(HealthPercent * 100))));
}

void UHealthBarWidget::SetTargetHealthComponent(UHealthComponent* HealthComponent)
{
	if (TargetHealthComponent == HealthComponent) return;
	
	if (TargetHealthComponent.IsValid())
	{
		TargetHealthComponent->OnHealthChanged.RemoveDynamic(this, &UHealthBarWidget::OnHealthChanged);
	}
	
	TargetHealthComponent = HealthComponent;
	
	if (TargetHealthComponent.IsValid())
	{
		TargetHealthComponent->OnHealthChanged.AddDynamic(this, &UHealthBarWidget::OnHealthChanged);
	}
}
