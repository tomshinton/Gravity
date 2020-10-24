// Gravity Project - Tom Shinton 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Pawn.h>

#include "GravityPawn.generated.h"

UCLASS(Blueprintable)
class AGravityPawn : public APawn
{
	GENERATED_BODY()

public:

	AGravityPawn(const FObjectInitializer& ObjectInitialiser);

private:	

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
