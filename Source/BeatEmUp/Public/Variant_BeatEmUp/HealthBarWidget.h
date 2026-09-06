// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UHealthComponent;

UCLASS()
class BEATEMUP_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	TWeakObjectPtr<UHealthComponent> TargetHealthComponent;
	
	UFUNCTION()
	void OnHealthChanged(float NewHealth, float MaxHealth);
	
protected:
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> HealthTextBlock;
	
public:
	
	UFUNCTION(BlueprintCallable)
	virtual void SetTargetHealthComponent(UHealthComponent* HealthComponent);
};
