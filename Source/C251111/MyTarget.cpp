// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTarget.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyTarget::AMyTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(32.f, 32.f, 32.f));

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Box);
	Sphere->SetRelativeScale3D(FVector(0.25f, 1.f, 1.f));

	Tags.Add(TEXT("Target"));
}

// Called when the game starts or when spawned
void AMyTarget::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

float AMyTarget::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), P_Explosion, GetActorLocation());

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Cue_Explosion, GetActorLocation());

	DoDesigner2();

	Destroy();

	return Damage;
}

void AMyTarget::DoDesigner2_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("C++ Base"));
}

int32 AMyTarget::GetGold()
{
	return 100;
}


