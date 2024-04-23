// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponent/InteractSphere/InteractSphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Interface/InteractInterface.h"

UInteractSphereComponent::UInteractSphereComponent()
{
	// Set collision profile
	this->SetCollisionProfileName("InteractProfile");
	this->ShapeColor = FColor::Green;

	this->OnComponentBeginOverlap.AddDynamic(this, &UInteractSphereComponent::OnBeginOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UInteractSphereComponent::OnEndOverlap);
}

void UInteractSphereComponent::CheckOverlaps()
{
	TArray<AActor*> OverlappingActors;
	this->GetOverlappingActors(OverlappingActors);

	AActor* BestTarget = nullptr;

	if (OverlappingActors.IsValidIndex(0))
	{
		BestTarget = OverlappingActors[0];
	}
	else
	{
		return;
	}

	if (OverlappingActors.Num() > 1)
	{

		for (const auto& Actor : OverlappingActors)
		{
			if (BestTarget == Actor)
			{
				continue;
			}

			const auto BestTargetDistance = UKismetMathLibrary::Vector_Distance(GetOwner()->GetActorLocation(), BestTarget->GetActorLocation());
			const auto NewTargetDistance = UKismetMathLibrary::Vector_Distance(GetOwner()->GetActorLocation(), Actor->GetActorLocation());

			if (BestTargetDistance > NewTargetDistance)
			{
				BestTarget = Actor;
			}
		}
	}

	if (BestTarget)
	{
		if (IInteractInterface::Execute_ShowCanInteract(BestTarget))
		{
			CurrentInteractTarget = BestTarget;

			OnFindInteractActor.Broadcast(CurrentInteractTarget);
		}
	}
}

void UInteractSphereComponent::OnBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UInteractInterface>())
	{
		if (IInteractInterface::Execute_IsCanInteract(OtherActor))
		{
			if (CurrentInteractTarget == OtherActor)
			{
				return;
			}

			// Check distance:
			if (CurrentInteractTarget)
			{
				const auto CurrentTargetDistance = UKismetMathLibrary::Vector_Distance(GetOwner()->GetActorLocation(), CurrentInteractTarget->GetActorLocation());
				const auto NewTargetDistance = UKismetMathLibrary::Vector_Distance(GetOwner()->GetActorLocation(), CurrentInteractTarget->GetActorLocation());

				if (CurrentTargetDistance < NewTargetDistance)
				{
					return;
				}
				else
				{
					IInteractInterface::Execute_UnShowCanInteract(CurrentInteractTarget);
				}
			}

			if (IInteractInterface::Execute_ShowCanInteract(OtherActor))
			{
				CurrentInteractTarget = OtherActor;

				OnFindInteractActor.Broadcast(CurrentInteractTarget);
			}
		}
	}
}

void UInteractSphereComponent::OnEndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CurrentInteractTarget == OtherActor)
	{
		IInteractInterface::Execute_UnShowCanInteract(CurrentInteractTarget);
		CurrentInteractTarget = nullptr;
	}
}
