// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPC.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


AMyPC::AMyPC()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>IMC_Default(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Input/IMC_P38.IMC_P38'"));
	if (IMC_Default.Succeeded())
	{
		InputMapping = IMC_Default.Object;
	}
}

void AMyPC::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(InputMapping, 0);
			}
		}
	}
}

void AMyPC::OnUnPossess()
{
	Super::OnUnPossess();
	if (IsLocalController())
	{
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(InputMapping);
			}
		}
	}
}

