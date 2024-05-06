// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FunctionLibrary/TT_269_Types.h"
#include "SaveGameActorComponent.generated.h"

class USaveGameSubsystem;
class USaveGameMain;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameData, USaveGameMain*, SaveGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadGameData, USaveGameMain*, SaveGame);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API USaveGameActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USaveGameActorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "SaveGame");
	FOnSaveGameData OnSaveGameData;

	UPROPERTY(BlueprintAssignable, Category = "SaveGame");
	FOnLoadGameData OnLoadGameData;

	/** Get save game object */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGame")
	USaveGameMain* GetSaveGameObject() const { return SaveGameObject; }

	/** Get Save game susystem */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGame")
	USaveGameSubsystem* GetSaveGameSubsystem() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGame")
	FORCEINLINE bool IsDynamicSpawn() const { return bIsDynamicSpawn; }

	UFUNCTION()
	void OwnerIsDestroed(AActor* DestroyedActor);

protected:
	static USaveGameSubsystem* SaveGameSubsytem;
	void LoadSaveGameSubsystem();

	UFUNCTION()
	void SaveGameData();

	static USaveGameMain* SaveGameObject;

	UFUNCTION()
	void ChangeSaveGameObject(USaveGameMain* NewSaveGameObject);

	UFUNCTION()
	void CheckSaveInfoByOwner();

private:
	bool bIsCheckSaveInfo = false;
	bool bIsDynamicSpawn = false;
	bool bIsDestroyedOnwer = false;
};
