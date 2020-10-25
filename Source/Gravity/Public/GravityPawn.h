// Gravity Project - Tom Shinton 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Pawn.h>

#include "GravityPawn.generated.h"

class UCapsuleComponent;
class UGravityMovementComponent;

UCLASS(Blueprintable)
class AGravityPawn : public APawn
{
	GENERATED_BODY()

public:

	AGravityPawn(const FObjectInitializer& ObjectInitialiser);

private:	

	UPROPERTY()
	UCapsuleComponent* PhysicsRoot;

	UPROPERTY()
	UGravityMovementComponent* MovementComponent;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
