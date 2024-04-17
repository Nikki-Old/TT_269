// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class USphereComponent;

UCLASS()
class TT_269_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Camera:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | Camera")
	USpringArmComponent* CameraSpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | Camera")
	UCameraComponent* MainCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | Camera")
	UArrowComponent* MainCameraForward = nullptr;

	/** For find with other can interact: */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	USphereComponent* InteractCollision = nullptr;

	// Movement logic:
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Movement")
	void MoveToForward(float Axis);
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Movement")
	void MoveToRight(float Axis);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
