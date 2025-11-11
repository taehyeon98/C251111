// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyRocket.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class C251111_API AMyRocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyRocket();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<UProjectileMovementComponent> RocketMove;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<UStaticMeshComponent> Rocket;
};
