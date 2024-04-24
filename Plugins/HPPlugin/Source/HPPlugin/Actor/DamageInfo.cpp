// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageInfo.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "HPPlugin/UI/ChangeValue/ChangeValueWidget.h"

// Sets default values
ADamageInfo::ADamageInfo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create WidgetComponent:
	DamageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	SetRootComponent(DamageWidgetComponent);

	DamageWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	DamageWidgetComponent->SetDrawAtDesiredSize(true);
}

// void ADamageInfoActor::SetLifeTimer()
//{
//	if (!GetWorld())
//		return;
//
//	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &ADamageInfoActor::DestroyEvent, LifeTime, false);
// }

void ADamageInfo::SetChangeValueType(EChangeValueType NewChangeValueType)
{
	ChangeValueType = NewChangeValueType;
}

// Called when the game starts or when spawned
void ADamageInfo::BeginPlay()
{
	Super::BeginPlay();

	// SetLifeTimer();
}

// Called every frame
void ADamageInfo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADamageInfo::UpdateDamageWidget(float Value, float Change)
{

	auto DamageWidgetClass = DamageWidgetClasses[ChangeValueType];

	// Set Widget Class:
	if (IsValid(DamageWidgetClass))
	{
		DamageWidgetComponent->SetWidgetClass(DamageWidgetClass);
	}

	LeftValue = Value;
	auto DamageWidget = Cast<UChangeValueWidget>(DamageWidgetComponent->GetUserWidgetObject());
	if (DamageWidget)
	{
		DamageWidget->InitEvent(this, Change);
	}
}

void ADamageInfo::DestroyEvent()
{
	this->Destroy();
}
