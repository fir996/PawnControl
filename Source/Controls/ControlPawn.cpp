// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPawn.h"
#include "Components/StaticMeshComponent.h"//网格模型
#include "Camera/CameraComponent.h"//相机
#include "Components/InputComponent.h"//项目设置输入

#include "MyMovementComponent.h"
#include "UObject/ConstructorHelpers.h"//将模型设置为网格
#include "Components/SphereComponent.h"//球型组件
#include "GameFrameWork/SpringArmComponent.h"//弹簧臂

// Sets default values
AControlPawn::AControlPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#if 1
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(80);//设置球体半径
	SphereComp->SetCollisionProfileName(TEXT("BlockAll"));//碰撞设置
	SphereComp->SetHiddenInGame(false);//游戏开始是否隐藏
	SetRootComponent(SphereComp);//使用球型组件作为根组件
#else
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//创建根组件
#endif
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));//创建网格
	MeshComponent->SetupAttachment(RootComponent);//将网格绑定在根组件下，GetRootComponent()获取根组件，也可以直接使用RootComponent,为保护类型，仅类内可用

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshComponentAsset.Succeeded()) {//判断是否设置成功
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);//将模型设置为网格体
		MeshComponent->SetRelativeLocation(FVector(0.f, 0, 0));//设置模型位置
	}

#if 1
	SprintArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintComp"));
	SprintArmComp->SetupAttachment(RootComponent);//绑定
	SprintArmComp->TargetArmLength = 400;//弹簧臂长度
	SprintArmComp->SetRelativeRotation(FRotator(-45.f, 0, 0));//相对位置
	SprintArmComp->bEnableCameraLag = true;//是否打开弹力
	SprintArmComp->CameraLagSpeed = 3;//设置弹速
#endif
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));//创建相机

#if 1
	Camera->SetupAttachment(SprintArmComp,USpringArmComponent::SocketName);//绑定到弹簧臂插槽
#else
	Camera->SetupAttachment(GetRootComponent());//绑定相机到根组件
	Camera->SetRelativeLocation(FVector(-300.f, 0, 300));//设置相对位置
	Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));//设置相对旋转
#endif
	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//玩家0获得本角色控制

	MovementComp = CreateDefaultSubobject<UMyMovementComponent>(TEXT("MovementComp"));
	MovementComp->UpdatedComponent = RootComponent;
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

	//UE_LOG(LogTemp,Warning,TEXT("CurrentVelocity:%f %f"),CurrentVelocity.X,CurrentVelocity.Y);
}

// Called to bind functionality to input
void AControlPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Forward", this, &AControlPawn::MoveForward);
	PlayerInputComponent->BindAxis("Move_Right", this, &AControlPawn::MoveRight);
}

#if 1
UPawnMovementComponent* AControlPawn::GetMovementComponent() const
{
	return MovementComp;
}

#endif

void AControlPawn::MoveForward(float Value) {
	//CurrentVelocity.X = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	//AddMovementInput(GetActorForwardVector() * Value);

	if (MovementComp)
	{
		MovementComp->AddInputVector(GetActorForwardVector() * Value);
	}
}



void AControlPawn::MoveRight(float Value) {
	//CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	//AddMovementInput(GetActorRightVector() * Value);
	if (MovementComp)
	{
		MovementComp->AddInputVector(GetActorRightVector() * Value);
	}
}

