// Gravity Project - Tom Shinton 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GravityPlayerController.generated.h"

UCLASS()
class GRAVITY_API AGravityPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AGravityPlayerController(const FObjectInitializer& ObjectInititaliser);

private:

	void BeginPlay() override;
	void AutoManageActiveCameraTarget(AActor* SuggestedTarget) override;
};
