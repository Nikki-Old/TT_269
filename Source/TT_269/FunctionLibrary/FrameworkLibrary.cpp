// Fill out your copyright notice in the Description page of Project Settings.

#include "FrameworkLibrary.h"
#include "GameInstance/GameInstanceMain.h"
#include "Controller/PlayerController/PlayerControllerMain.h"

UGameInstanceMain* UFrameworkLibrary::GetGameInstanceMain(const UObject* World)
{
	if (World)
	{
		auto WorldContext = GEngine->GetWorldFromContextObject(World, EGetWorldErrorMode::LogAndReturnNull);
		if (WorldContext)
		{
			auto GameInstance = WorldContext->GetGameInstance();
			if (GameInstance)
			{
				const auto GameInstanceMain = Cast<UGameInstanceMain>(GameInstance);
				return GameInstanceMain;
			}
		}
	}
	return nullptr;
}

APlayerControllerMain* UFrameworkLibrary::GetPlayerControllerMain(const APawn* PlayerPawn)
{
	if (PlayerPawn)
	{
		return Cast<APlayerControllerMain>(PlayerPawn->GetController());
	}
	return nullptr;
}
