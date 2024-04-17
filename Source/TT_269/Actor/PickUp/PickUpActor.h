// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpActor.generated.h"

class USphereComponent;

UCLASS()
class TT_269_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Root component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	USceneComponent* SceneComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
