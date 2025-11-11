// Fill out your copyright notice in the Description page of Project Settings.


#include "MyRocket.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AMyRocket::AMyRocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(25.0f, 11.0f, 7.0f));

	Rocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rocket"));
	Rocket->SetupAttachment(Box);
	Rocket->AddRelativeRotation(FRotator(-90.0f,0,0));
	

	RocketMove = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("RocketMove"));
	RocketMove->InitialSpeed = 1200.0f;
	RocketMove->MaxSpeed = 1200.0f;
	RocketMove->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMyRocket::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);
	
	OnActorBeginOverlap.AddDynamic(this, &AMyRocket::ProcessBeginOverlap);
}

// Called every frame
void AMyRocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyRocket::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag(TEXT("Target")))
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			10.0f,
			UGameplayStatics::GetPlayerController(GetWorld(), 0),
			this,
			UDamageType::StaticClass()
		);

		Destroy();
	}

}

