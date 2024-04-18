// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponent/InteractSphere/InteractSphereComponent.h"

UInteractSphereComponent::UInteractSphereComponent()
{
	// Set collision profile
	this->SetCollisionProfileName("InteractProfile");
	
	this->OnComponentBeginOverlap.AddDynamic(this, &UInteractSphereComponent::OnBeginOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UInteractSphereComponent::OnEndOverlap);
}

void UInteractSphereComponent::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UInteractSphereComponent::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
