// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "PTPlayerController.h"

AMyGameMode::AMyGameMode()
{
	PlayerControllerClass = APTPlayerController::StaticClass();
}

