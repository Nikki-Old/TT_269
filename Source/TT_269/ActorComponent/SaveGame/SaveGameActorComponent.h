// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/SavableObject.h"
#include "Subsystem/SaveGameSubsystem.h"
#include "SaveGameActorComponent.generated.h"

class USaveGameSubsystem;
class USaveGameMain;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSaveGameData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadGameData);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TT_269_API USaveGameActorComponent : public UActorComponent, public ISavableObject
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USaveGameActorComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

#pragma region ISavableObject
	/** Get Save Data */
	virtual bool GetActorSaveData_Implementation(FActorSaveData& SaveData);

	/** Set Save Data */
	virtual bool LoadActorSaveData_Implementation(const FActorSaveData& SaveData);
#pragma endregion

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
	FORCEINLINE bool IsDynamicSpawn() const { return bIsSpawnedOwner; }

	UFUNCTION()
	void OwnerIsDestroed(AActor* DestroyedActor);

protected:
	static USaveGameSubsystem* SaveGameSubsytem;
	void LoadSaveGameSubsystem();

	static USaveGameMain* SaveGameObject;

	UFUNCTION()
	void ChangeSaveGameObject(USaveGameMain* NewSaveGameObject);

	void LoadOwnerComponentsBinaryData(const TMap<FString, FActorComponentSaveData>& ComponentsBinaryData);
	void GetOwnerComponentsBinaryData(TMap<FString, FActorComponentSaveData>& ComponentsBinaryData);

private:
	bool bIsSpawnedOwner = false;
	bool bIsDestroyedOnwer = false;

};
