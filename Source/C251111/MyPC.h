// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPC.generated.h"

class UInputMappingContext;
/**
 * 
 */
UCLASS()
class C251111_API AMyPC : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPC();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> InputMapping;
};
