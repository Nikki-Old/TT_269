// Fill out your copyright notice in the Description page of Project Settings.

#include "ChangeValueWidget.h"

#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "HPPlugin/Actor/DamageInfo.h"
#include "HPPlugin/ActorComponent/HealthComponent.h"

bool UChangeValueWidget::Initialize()
{
	return Super::Initialize();
}

void UChangeValueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (TXTValueChange)
	{
		TXTValueChange->TextDelegate.BindUFunction(this, TEXT("GetValueChangeTXT"));
		TXTValueChange->ColorAndOpacityDelegate.BindUFunction(this, TEXT("GetColorTXTValueChange"));
	}

	ValueWidgetAnimIsEnd.BindDynamic(this, &UChangeValueWidget::AnimationIsEnd);

	// Bind to AnimationFinished Delegate and AnimationIsEnd:
	if (TXTValueChangeAnim)
	{
		BindToAnimationFinished(TXTValueChangeAnim, ValueWidgetAnimIsEnd);
	}
}

void UChangeValueWidget::InitEvent_Implementation(AActor* Owner, float Change)
{
	checkf(Owner, TEXT("Owner is NULL"));

	// Set Owneractor:
	OwnerActor = Cast<ADamageInfo>(Owner);

	check(OwnerActor);

	/* Save current Change: **/
	SetValueChangeInTextBlock(Change);

	// Play animation:
	if (TXTValueChangeAnim)
	{
		PlayAnimation(TXTValueChangeAnim);
	}
}

void UChangeValueWidget::SetValueChangeInTextBlock_Implementation(float Change)
{

	ValueChange = Change;

	/* Set Color for TXT: **/
	TXTValueChange->ColorAndOpacity = GetColorTXTValueChange();

	if (TXTValueChange)
	{
		TXTValueChange->SetText(GetValueChangeTXT());
	}
}

FText UChangeValueWidget::GetValueChangeTXT() const
{
	TEnumAsByte<ERoundingMode> RoundingMode = ERoundingMode::HalfFromZero;
	return UKismetTextLibrary::Conv_FloatToText(ValueChange, RoundingMode, true, true, 1, 3, 0, 0);
}

void UChangeValueWidget::AnimationIsEnd()
{
	if (OwnerActor)
		OwnerActor->DestroyEvent();
}

/* FLinearColor UTPSChangeHealthWidgetBase::GetColorHealthChange() const
{
	return HealthChangeColor;
}*/

FSlateColor UChangeValueWidget::GetColorTXTValueChange()
{
	if (ValueChange == 0.0f || !OwnerActor)
		return FSlateColor(BaseColor);

	float CurrentHeath = OwnerActor->GetLeftValue();

	// TO DO: Fix bug:
	// Improved, inctorrect color calcuclations. Must be GREEN to RED:
	BaseColor.R = UKismetMathLibrary::MapRangeClamped(CurrentHeath, 0.0f, MAX_FLT, 1.0f, 0.0f);
	BaseColor.G = UKismetMathLibrary::MapRangeClamped(CurrentHeath, 0.0f, MAX_FLT, 0.0f, 1.0f);

	BaseColor.B = 0.0f;
	return FSlateColor(BaseColor);
}
