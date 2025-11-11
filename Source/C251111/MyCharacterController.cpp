// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AMyCharacterController::AMyCharacterController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>Input(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_Default.IMC_Default'"));
	if (Input.Succeeded())
	{
		InputMove = Input.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>Input_Aim(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_MouseLook.IMC_MouseLook'"));
	if (Input_Aim.Succeeded())
	{
		InputMouseAim = Input_Aim.Object;
	}

}

void AMyCharacterController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(InputMove, 0);
				InputSystem->AddMappingContext(InputMouseAim, 0);
			}
		}
	}
}

void AMyCharacterController::OnUnPossess()
{
	Super::OnUnPossess();
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(InputMove);
				InputSystem->RemoveMappingContext(InputMouseAim);
			}
		}
	}
}
