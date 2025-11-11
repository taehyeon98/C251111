// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyP38.generated.h"

class UStaticMeshComponent;
class UArrowComponent;
class UFloatingPawnMovement;
class UCameraComponent;
class USpringArmComponent;
class UBoxComponent;
struct FInputActionValue;

UCLASS()
class C251111_API AMyP38 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyP38();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnhancedFire(const FInputActionValue& Value);
	void ProcessMovement(const FInputActionValue& Value);

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Component)
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Component)
	TObjectPtr<UStaticMeshComponent> Left;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Component)
	TObjectPtr<UStaticMeshComponent> Right;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = Component)
	TObjectPtr<UArrowComponent> Arrow;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<USpringArmComponent> Spring;

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere,Category = Component)
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = Input)
	TObjectPtr<class UInputAction> IA_Movement;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category = Input)
	TObjectPtr<class UInputAction> IA_Fire;
};
