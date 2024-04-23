// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponProjectileMain.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponProjectileMain::AWeaponProjectileMain()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere")); // what touches with other actor's

	Collision->SetSphereRadius(15.0f);
	Collision->bReturnMaterialOnMove = true;	  // hit event return physMaterial
	Collision->SetCanEverAffectNavigation(false); // collision not affect navigation (P keybord on editor)
	// Set the sphere's collision profile name to "Projectile"
	Collision->BodyInstance.SetCollisionProfileName(TEXT("WeaponProjectile"));

	// Event's:
	Collision->OnComponentHit.AddDynamic(this, &AWeaponProjectileMain::CollisionHit);					// Hit
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponProjectileMain::CollisionBeginOverlap); // Begin Overlap
	Collision->OnComponentEndOverlap.AddDynamic(this, &AWeaponProjectileMain::CollisionEndOverlap);		// EndOverlap

	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh component"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCanEverAffectNavigation(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement component"));
	// What object we update?
	ProjectileMovement->UpdatedComponent = RootComponent; // SetUpdatedComponent(RootComponent);

	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AWeaponProjectileMain::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponProjectileMain::InitProjectile(FProjectileInfo InitParam)
{
	// Set speed:
	ProjectileMovement->InitialSpeed = InitParam.InitialSpeed;
	ProjectileMovement->MaxSpeed = InitParam.InitialSpeed;

	this->SetLifeSpan(InitParam.LifeTime);

	if (InitParam.Mesh)
	{
		Mesh->SetStaticMesh(InitParam.Mesh);
	}

	ProjectileInfo = InitParam;
}

void AWeaponProjectileMain::CollisionHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Apply Damage:
	UGameplayStatics::ApplyPointDamage(OtherActor, ProjectileInfo.Damage, Hit.Location, Hit, GetInstigatorController(), GetOwner()->GetOwner(), NULL);

	ImpactProjectile();
}

void AWeaponProjectileMain::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeaponProjectileMain::CollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeaponProjectileMain::ImpactProjectile()
{
	this->Destroy();
}

// Called every frame
void AWeaponProjectileMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
