// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPawn.h"
#include "Components/StaticMeshComponent.h"//����ģ��
#include "Camera/CameraComponent.h"//���
#include "Components/InputComponent.h"//��Ŀ��������

// Sets default values
AControlPawn::AControlPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//���������
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));//��������
	MeshComponent->SetupAttachment(GetRootComponent());//��������ڸ������GetRootComponent()��ȡ�������Ҳ����ֱ��ʹ��RootComponent,Ϊ�������ͣ������ڿ���

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));//�������
	Camera->SetupAttachment(GetRootComponent());//������������
	Camera->SetRelativeLocation(FVector(-300.f, 0, 300));//�������λ��
	Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));//���������ת
	
	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//���0��ñ���ɫ����
}

// Called when the game starts or when spawned
void AControlPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AControlPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
	SetActorLocation(NewLocation);

	UE_LOG(LogTemp,Warning,TEXT("CurrentVelocity:%f %f"),CurrentVelocity.X,CurrentVelocity.Y);
}

// Called to bind functionality to input
void AControlPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Forward", this, &AControlPawn::MoveForward);
	PlayerInputComponent->BindAxis("Move_Right", this, &AControlPawn::MoveRight);
}

void AControlPawn::MoveForward(float Value) {
	CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;

}

void AControlPawn::MoveRight(float Value) {
	CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;

}

