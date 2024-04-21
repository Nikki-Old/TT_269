// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DistanceWeaponMain.generated.h"

UCLASS()
class TT_269_API ADistanceWeaponMain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADistanceWeaponMain();

	void SetWeaponReady(bool bIsReady);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
