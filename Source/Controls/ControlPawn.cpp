// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlPawn.h"
#include "Components/StaticMeshComponent.h"//����ģ��
#include "Camera/CameraComponent.h"//���
#include "Components/InputComponent.h"//��Ŀ��������

#include "MyMovementComponent.h"
#include "UObject/ConstructorHelpers.h"//��ģ������Ϊ����
#include "Components/SphereComponent.h"//�������
#include "GameFrameWork/SpringArmComponent.h"//���ɱ�

// Sets default values
AControlPawn::AControlPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#if 1
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(80);//��������뾶
	SphereComp->SetCollisionProfileName(TEXT("BlockAll"));//��ײ����
	SphereComp->SetHiddenInGame(false);//��Ϸ��ʼ�Ƿ�����
	SetRootComponent(SphereComp);//ʹ�����������Ϊ�����
#else
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));//���������
#endif
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));//��������
	MeshComponent->SetupAttachment(RootComponent);//��������ڸ�����£�GetRootComponent()��ȡ�������Ҳ����ֱ��ʹ��RootComponent,Ϊ�������ͣ������ڿ���

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshComponentAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (MeshComponentAsset.Succeeded()) {//�ж��Ƿ����óɹ�
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);//��ģ������Ϊ������
		MeshComponent->SetRelativeLocation(FVector(0.f, 0, 0));//����ģ��λ��
	}

#if 1
	SprintArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintComp"));
	SprintArmComp->SetupAttachment(RootComponent);//��
	SprintArmComp->TargetArmLength = 400;//���ɱ۳���
	SprintArmComp->SetRelativeRotation(FRotator(-45.f, 0, 0));//���λ��
	SprintArmComp->bEnableCameraLag = true;//�Ƿ�򿪵���
	SprintArmComp->CameraLagSpeed = 3;//���õ���
#endif
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));//�������

#if 1
	Camera->SetupAttachment(SprintArmComp,USpringArmComponent::SocketName);//�󶨵����ɱ۲��
#else
	Camera->SetupAttachment(GetRootComponent());//������������
	Camera->SetRelativeLocation(FVector(-300.f, 0, 300));//�������λ��
	Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));//���������ת
#endif
	CurrentVelocity = FVector(0.f);
	MaxSpeed = 100.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;//���0��ñ���ɫ����

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

