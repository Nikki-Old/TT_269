// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageInfo.generated.h"

class UChangeValueWidget;
class UWidgetComponent;

UENUM(BlueprintType)
enum class EChangeValueType : uint8
{
	None_Type UMETA(DisplayName = "None"),
	Damage_Type UMETA(DisplayName = "Damage"),
	OneHit_Type UMETA(DisplayName = "OneHit")
};

UCLASS()
class HPPLUGIN_API ADamageInfo : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageInfo();

	/** Widget component: */
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Damage")
	UWidgetComponent* DamageWidgetComponent = nullptr;

	UFUNCTION()
	void SetChangeValueType(EChangeValueType NewChangeValueType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Damage")
	float LeftValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	EChangeValueType ChangeValueType = EChangeValueType::None_Type;

	/** Widget class: */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TMap<EChangeValueType, TSubclassOf<UChangeValueWidget>> DamageWidgetClasses;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Get Value(Health or shield point and etc.) and Change this Value: */
	UFUNCTION(BLueprintCallable, Category = "Damage")
	void UpdateDamageWidget(float Value, float Change);

	UFUNCTION(BLueprintCallable, Category = "Damage")
	void DestroyEvent();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetLeftValue() const { return LeftValue; }
};
