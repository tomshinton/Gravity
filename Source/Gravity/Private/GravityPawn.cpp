// Gravity Project - Tom Shinton 2020

#include "Gravity/Public/GravityPawn.h"

#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include <Runtime/Camera/Public/GravityCamera.h>

AGravityPawn::AGravityPawn(const FObjectInitializer& ObjectInitialiser)
	: Super(ObjectInitialiser)
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

void AGravityPawn::BeginPlay()
{
	Super::BeginPlay();

//#if WITH_CLIENT_CODE
//	if (GetNetMode() != NM_DedicatedServer)
//	{

//	}
//#endif //WITH_CLIENT_CODE
}

void AGravityPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGravityPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

