// Fill out your copyright notice in the Description page of Project Settings.

#include "Gravity/Public/GravityGameModeBase.h"

#include "Gravity/Public/GravityPawn.h"
#include "Gravity/Public/GravityPlayerController.h"

AGravityGameModeBase::AGravityGameModeBase()
{
	DefaultPawnClass = AGravityPawn::StaticClass();
	PlayerControllerClass = AGravityPlayerController::StaticClass();
}
