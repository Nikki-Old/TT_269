// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Interface/InteractInterface.h"

#include "PickUpActor.generated.h"

class USphereComponent;
class UItemDataAsset;
class USaveGameActorComponent;
class USaveGameMain;

//USTRUCT(BlueprintType)
//struct FPickUpActorSaveInfo
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnyWhere, BlueprintReadWite, Category = "SaveGame")
//	int32 Quantity = 0;
//};

UCLASS()
class TT_269_API APickUpActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpActor();

	/** Save game actor component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SaveGame")
	USaveGameActorComponent* SaveGameComponent = nullptr;

	/** Get PickUpDataAsset */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PickUp")
	void GetItemDataAsset(UItemDataAsset*& OutInfo) const { OutInfo = ItemDataAsset; }

#pragma region IInteractInterface

	/** Target actor can start interact? */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool IsCanInteract() const;
	bool IsCanInteract_Implementation() const;

	/** Show signal: "Can interact!" */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool ShowCanInteract();
	bool ShowCanInteract_Implementation();

	/** Un show signal: "Can interact!" */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool UnShowCanInteract();
	bool UnShowCanInteract_Implementation();

	/** Start interact with param: Instigator interaction.  */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool StartInteract(AActor* InteractInstigator);
	bool StartInteract_Implementation(AActor* InteractInstigator);

	/** Stop interact */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool StopInteract();
	bool StopInteract_Implementation();

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Root component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	USceneComponent* SceneComponent = nullptr;

	/** Data asset for this actor with name and type */
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, SaveGame, Category = "PickUp", meta = (ExposeOnSpawn = true))
	UItemDataAsset* ItemDataAsset = nullptr;

	/** Initialize metod: */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PickUp")
	void Initialize();
	void Initialize_Implementation();

	UPROPERTY(BlueprintReadWrite, SaveGame, Category = "PickUp")
	bool bIsInitialized = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
