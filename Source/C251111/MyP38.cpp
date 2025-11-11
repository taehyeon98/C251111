// Fill out your copyright notice in the Description page of Project Settings.


#include "MyP38.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyRocket.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"


// Sets default values
AMyP38::AMyP38()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(47.000000, 70.000000, 15.000000));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetRelativeLocation(FVector(37.000000, 21.000000, 0.000000));

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetRelativeLocation(FVector(37.000000, -21.000000, 0.000000));

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);
	Arrow->SetRelativeLocation(FVector(78.000000, 0.000000, 0.000000));

	Spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring"));
	Spring->SetupAttachment(Box);
	Spring->SocketOffset = FVector(0.000000, 0.000000, 60.000000);
	Spring->bDoCollisionTest = false;
	Spring->bEnableCameraLag = true;
	Spring->bEnableCameraRotationLag = true;
	Spring->CameraLagMaxDistance = 100.0f;
	Spring->CameraLagSpeed = 10.0f;
	Spring->CameraRotationLagSpeed = 30.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Spring);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	Movement->MaxSpeed = 200.0f;

	static ConstructorHelpers::FObjectFinder<UInputAction>Fire(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Fire.IA_Fire'"));
	if (Fire.Succeeded())
	{
		IA_Fire = Fire.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>Move(TEXT("/Script/EnhancedInput.InputAction'/Game/Input/IA_Movement.IA_Movement'"));
	if (Move.Succeeded())
	{
		IA_Movement = Move.Object;
	}
}

// Called when the game starts or when spawned
void AMyP38::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyP38::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector());
	Left->AddRelativeRotation(FRotator( 0, 0, 3500 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
	Right->AddRelativeRotation(FRotator( 0, 0, 3500 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

// Called to bind functionality to input
void AMyP38::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// 여기에서 'ETriggerEvent' 열거형 값을 변경하여 원하는 트리거 이벤트를 바인딩할 수 있습니다.
	Input->BindAction(IA_Fire, ETriggerEvent::Started, this, &AMyP38::EnhancedFire);
	Input->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &AMyP38::ProcessMovement);
}

void AMyP38::EnhancedFire(const FInputActionValue& Value)
{
	GetWorld()->SpawnActor<AMyRocket>(AMyRocket::StaticClass(), Arrow->K2_GetComponentToWorld());
}

void AMyP38::ProcessMovement(const FInputActionValue& Value)
{
	FVector2D Moving = Value.Get<FVector2D>();
	Moving = Moving * 60 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());

	AddActorLocalRotation(FRotator(Moving.Y, 0, Moving.X));
}
