// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponMain.h"
#include "FunctionLibrary/FrameworkLibrary.h"
#include "GameInstance/GameInstanceMain.h"

UGameInstanceMain* AWeaponMain::GameInstanceMain = nullptr;

// Sets default values
AWeaponMain::AWeaponMain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponMain::BeginPlay()
{
	Super::BeginPlay();

	if (!GameInstanceMain)
	{
		GameInstanceMain = UFrameworkLibrary::GetGameInstanceMain(GetWorld());
	}

	InitializeWeapon();
}

void AWeaponMain::InitializeWeapon()
{
	if (GameInstanceMain)
	{
		if (GameInstanceMain->GetWeaponInfoByName(WeaponName, WeaponActorInfo))
		{
			OnWeaponIsInitialized.Broadcast();
		}
	}
}

// Called every frame
void AWeaponMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponMain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (EndPlayReason == EEndPlayReason::Quit || EndPlayReason == EEndPlayReason::EndPlayInEditor)
	{
		GameInstanceMain = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}
