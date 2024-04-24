// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChangeValueWidget.generated.h"

class ADamageInfo;
class UTextBlock;

/**
 *
 */

UCLASS()
class HPPLUGIN_API UChangeValueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/** Function for binds WidgetComonents. */
	virtual bool Initialize() override;

	/* Override base function. */
	virtual void NativeConstruct() override;

	/** Text block for display value "HealthChange"*/
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXTValueChange = nullptr;

	/** Initialize function, is spawn this widget need call this event: */
	UFUNCTION(BlueprintNativeEvent, Category = "ChangeValueWidget")
	void InitEvent(AActor* Owner, const float Change);
	void InitEvent_Implementation(AActor* Owner, const float Change);

	FWidgetAnimationDynamicEvent ValueWidgetAnimIsEnd;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "ChangeValueWidget")
	void SetValueChangeInTextBlock(const float Change);
	void SetValueChangeInTextBlock_Implementation(const float Change);

	// Set Color:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ChangeValueWidget")
	FSlateColor GetColorTXTValueChange();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ChangeValueWidget")
	FText GetValueChangeTXT() const;

	/** Owner Actor */
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "ChangeValueWidget")
	ADamageInfo* OwnerActor = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* TXTValueChangeAnim = nullptr;

private:
	FLinearColor BaseColor = FLinearColor::White;
	// Change:
	float ValueChange = 0.0f;

	/** Animation is end event: */
	UFUNCTION()
	void AnimationIsEnd();

	// Color TXT:
	// FLinearColor HealthChangeColor;
};
