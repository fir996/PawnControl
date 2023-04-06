// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMovementComponent.h"

void UMyMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime)) {
		return;
	}
	FVector DeltaMovement = ConsumeInputVector().GetClampedToMaxSize(1) * DeltaTime * 150;

	if (!DeltaMovement.IsNearlyZero()){
		FHitResult HitResult;
		SafeMoveUpdatedComponent(DeltaMovement,UpdatedComponent->GetComponentRotation(),true, HitResult);

		if (HitResult.IsValidBlockingHit())
		{
			SlideAlongSurface(DeltaMovement, 1 - HitResult.Time, HitResult.Normal, HitResult);
		}
	}

	

}
