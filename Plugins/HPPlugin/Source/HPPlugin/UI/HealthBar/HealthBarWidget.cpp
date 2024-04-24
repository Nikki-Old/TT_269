// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"
#include "HPPlugin/ActorComponent/HealthComponent.h"

bool UHealthBarWidget::Initialize()
{
	return Super::Initialize();
}

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHealthBarWidget::CreateConnectWithHealthComponent_Implementation(UHealthComponent* NewHealthComponent)
{
	if (NewHealthComponent)
	{
		OwnerHealthComponent = NewHealthComponent;
		MaxHealth = OwnerHealthComponent->GetMaxHealth();
		CurrentHealth = OwnerHealthComponent->GetHealth();

		if (!OwnerHealthComponent->OnChangeHealth.IsAlreadyBound(this, &UHealthBarWidget::ChangeHealth))
		{
			OwnerHealthComponent->OnChangeHealth.AddDynamic(this, &UHealthBarWidget::ChangeHealth);
		}

		if (!OwnerHealthComponent->OnChangeMaxHealth.IsAlreadyBound(this, &UHealthBarWidget::ChangeMaxHealth))
		{
			OwnerHealthComponent->OnChangeMaxHealth.AddDynamic(this, &UHealthBarWidget::ChangeMaxHealth);
		}
	}
}

void UHealthBarWidget::ChangeHealth_Implementation(AActor* Owner, float NewCurrentHealth, float Change)
{
	// BP:
	this->CurrentHealth = NewCurrentHealth;
}

void UHealthBarWidget::ChangeMaxHealth_Implementation(AActor* Owner, float OldMaxHealth, float NewMaxHealth)
{
	this->MaxHealth = NewMaxHealth;
}
