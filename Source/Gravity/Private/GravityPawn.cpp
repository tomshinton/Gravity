// Gravity Project - Tom Shinton 2020

#include "Gravity/Public/GravityPawn.h"

#include <Runtime/Engine/Classes/Components/CapsuleComponent.h>
#include <Runtime/Engine/Classes/GameFramework/PlayerController.h>
#include <Runtime/Camera/Public/GravityCamera.h>
#include <Runtime/Movement/Public/GravityMovementComponent.h>

namespace GravityPawnPrivate
{
	const FName PhysicsRootName = TEXT("PhysicsRoot");
	const FName MovementComponentName = TEXT("MovementComponent");
}

AGravityPawn::AGravityPawn(const FObjectInitializer& ObjectInitialiser)
	: Super(ObjectInitialiser)
	, PhysicsRoot(ObjectInitialiser.CreateDefaultSubobject<UCapsuleComponent>(this, GravityPawnPrivate::PhysicsRootName))
	, MovementComponent(ObjectInitialiser.CreateDefaultSubobject<UGravityMovementComponent>(this, GravityPawnPrivate::MovementComponentName))
{
	SetRootComponent(PhysicsRoot);

	SetPhysicsState(*PhysicsRoot);

	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
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

void AGravityPawn::SetPhysicsState(UPrimitiveComponent& InComponent)
{
	InComponent.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	InComponent.GetBodyInstance()->bLockXRotation = true;
	InComponent.GetBodyInstance()->bLockYRotation = true;
	InComponent.GetBodyInstance()->bLockZRotation = true;

	InComponent.GetBodyInstance()->bLockXTranslation = true;
}

