// Fill out your copyright notice in the Description page of Project Settings.

#include "Gravity/Public/GravityPawn.h"

AGravityPawn::AGravityPawn(const FObjectInitializer& ObjectInitialiser)
	: Super(ObjectInitialiser)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGravityPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AGravityPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGravityPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

