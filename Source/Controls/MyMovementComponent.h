// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CONTROLS_API UMyMovementComponent : public UPawnMovementComponent//UGDC_API
{
	GENERATED_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
