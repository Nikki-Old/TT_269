// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Controller/PlayerController/PlayerControllerMain.h"
#include "FunctionLibrary/FrameworkLibrary.h"
#include "ActorComponent/InteractSphere/InteractSphereComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create camera spring arm and set settings:
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("CameraSpringArm");
	CameraSpringArm->SetupAttachment(GetCapsuleComponent());
	CameraSpringArm->bDoCollisionTest = false;

	// Create camera and set settings:
	MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	MainCamera->SetupAttachment(CameraSpringArm, CameraSpringArm->SocketName);

	// Create arrow for camera forward vector:
	MainCameraForward = CreateDefaultSubobject<UArrowComponent>("MainCameraForward");
	MainCameraForward->SetupAttachment(MainCamera);

	// Create interact collision:
	InteractSphere = CreateDefaultSubobject<UInteractSphereComponent>("InteractCollision");
	InteractSphere->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//// Save offset:
	//RotationOffset = GetMesh()->GetRelativeRotation();

}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	if (NewController)
	{
		PlayerController = Cast<APlayerControllerMain>(NewController);
		
		if (!PlayerController)
		{
			return;
		}

		PlayerController->bShowMouseCursor = true;
	}
	Super::PossessedBy(NewController);
}

void APlayerCharacter::MoveToForward(float Axis)
{
	// Movement direction = Capsule forward vecror * Axis:
	this->AddMovementInput((MainCameraForward->GetForwardVector() * Axis));
}

void APlayerCharacter::MoveToRight(float Axis)
{
	// Movement direction = Capsule right vecror * Axis:
	this->AddMovementInput((MainCamera->GetRightVector() * Axis));
}

void APlayerCharacter::UpdateMeshRotationByCursorHit()
{
	auto TargetRotationOffset = UKismetMathLibrary::FindLookAtRotation(GetMesh()->GetComponentLocation(), UnderCursorHitResult.Location);
	TargetRotationOffset.Pitch = 0;
	TargetRotationOffset.Roll = 0;
	this->SetActorRotation(TargetRotationOffset);
}

void APlayerCharacter::UpdateUnderCursorHitResult()
{
	if (PlayerController)
	{
		PlayerController->GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, UnderCursorHitResult);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateUnderCursorHitResult();
	UpdateMeshRotationByCursorHit();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
