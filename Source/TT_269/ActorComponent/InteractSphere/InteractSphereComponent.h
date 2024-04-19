// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractSphereComponent.generated.h"

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFindInteractActor, AActor*, NewTargetActor);

UCLASS()
class TT_269_API UInteractSphereComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UInteractSphereComponent();

	UPROPERTY(BlueprintAssignable, Category = "InteractSphere")
	FOnFindInteractActor OnFindInteractActor;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "InteractSphere")
	FORCEINLINE AActor* GetCurrentInteractTarget() const { return CurrentInteractTarget; };

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "InteractSphere")
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = "InteractSphere")
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	void OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY()
	AActor* CurrentInteractTarget = nullptr;
};
