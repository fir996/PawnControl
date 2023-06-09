// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ControlPawn.generated.h"

UCLASS()
class CONTROLS_API AControlPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AControlPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SprintArmComp;

#if 1
	UPROPERTY(VisibleAnywhere)
	class UMyMovementComponent* MovementComp;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
#endif
private:
	void MoveForward(float Value);//ǰ��
	void MoveRight(float Value);//����

};
