// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

/**
 *
 */

class UHealthComponent;

UCLASS()
class HPPLUGIN_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/* Override base function. */
	virtual bool Initialize() override;

	/* Override base function. */
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HealthBarWidget")
	void CreateConnectWithHealthComponent(UHealthComponent* NewHealthComponent);
	void CreateConnectWithHealthComponent_Implementation(UHealthComponent* NewHealthComponent);

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HealthBarWidget")
	void ChangeHealth(AActor* Owner, float NewCurrentHealth, float Change);
	void ChangeHealth_Implementation(AActor* Owner, float NewCurrentHealth, float Change);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HealthBarWidget")
	void ChangeMaxHealth(AActor* Owner, float OldMaxHealth, float NewMaxHealth);
	void ChangeMaxHealth_Implementation(AActor* Owner, float OldMaxHealth, float NewMaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "HealthBarWidget")
	float CurrentHealth = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "HealthBarWidget")
	float MaxHealth = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "HealthBarWidget")
	UHealthComponent* OwnerHealthComponent = nullptr;
};
