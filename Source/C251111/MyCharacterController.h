// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class C251111_API AMyCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyCharacterController();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMove;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMouseAim;
};
