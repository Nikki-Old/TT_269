// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyCharacterMain.h"

// Sets default values
AEnemyCharacterMain::AEnemyCharacterMain()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacterMain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacterMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacterMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

