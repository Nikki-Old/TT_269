// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveGameActorComponent.generated.h"

class USaveGameSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUpdateSaveGameData, bool, bIsSave, FName, ActorName, USaveGameSubsystem*, SaveGameSubsytem);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API USaveGameActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USaveGameActorComponent();

	UPROPERTY(BlueprintAssignable, Category = SaveGame);
	FOnUpdateSaveGameData OnUpdateSaveGameData;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void LoadSaveGameSubsystem();

	static USaveGameSubsystem* SaveGameSubsytem;

	/** Get Save game susystem */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGame")
	USaveGameSubsystem* GetSaveGameSubsystem() const;

	UFUNCTION()
	void OnSaveGameData();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
