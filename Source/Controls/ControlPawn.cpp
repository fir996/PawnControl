// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPawn.h"
#include "Components/StaticMeshComponent.h"//网格模型
#include "Camera/CameraComponent.h"//相机
#include "Components/InputComponent.h"//项目设置输入

// Sets default values
AControlPawn::AControlPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建跟组件
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));//创建网格
	MeshComponent->SetupAttachment(GetRootComponent());//将网格绑定在根组件下GetRootComponent()获取根组件，也可以直接使用RootComponent,为保护类型，仅类内可用

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));//创建相机
	Camera->SetupAttachment(GetRootComponent());//绑定相机到根组件
	Camera->SetRelativeLocation(FVector(-300.f, 0, 300));//设置相对位置
	Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));//设置相对旋转
	
	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//玩家0获得本角色控制
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

