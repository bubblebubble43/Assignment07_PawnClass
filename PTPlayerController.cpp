// Fill out your copyright notice in the Description page of Project Settings.


#include "PTPlayerController.h"
#include "EnhancedInputSubsystems.h" //Local Player Subsystem

APTPlayerController::APTPlayerController()
    : InputMappingContext(nullptr),
    MoveAction(nullptr),
    JumpAction(nullptr),
    LookAction(nullptr),
    SprintAction(nullptr)
{
}

void APTPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (InputMappingContext)
            {
                Subsystem->AddMappingContext(InputMappingContext, 0);
            }
        }
    }
}