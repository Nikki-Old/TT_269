// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class USphereComponent;
class UInteractSphereComponent;
class APlayerControllerMain;

UCLASS()
class TT_269_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Get controller this pawn */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCharacter")
	APlayerControllerMain* GetPlayerControllerMain() const { return PlayerController; }

	/** Get hit result under cursor */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "PlayerCharacter")
	void GetUnderCursorHitResult(FHitResult& OutInfo) const { OutInfo = UnderCursorHitResult; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Override method */
	virtual void PossessedBy(AController* NewController) override;

	// Camera:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | Camera")
	USpringArmComponent* CameraSpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | Camera")
	UCameraComponent* MainCamera = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerCharacter | Camera")
	UArrowComponent* MainCameraForward = nullptr;

	/** For find with other can interact: */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp")
	UInteractSphereComponent* InteractSphere = nullptr;

	// Movement logic:
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Movement")
	void MoveToForward(float Axis);
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacter | Movement")
	void MoveToRight(float Axis);

	UFUNCTION()
	void UpdateMeshRotationByCursorHit();

	UFUNCTION()
	void UpdateUnderCursorHitResult();

protected:
	/** Controller this pawn **/
	UPROPERTY(BlueprintReadWrite, Category = "PlayerCharacter")
	APlayerControllerMain* PlayerController = nullptr;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FHitResult UnderCursorHitResult = FHitResult();
	//FRotator RotationOffset = FRotator(0);
};
