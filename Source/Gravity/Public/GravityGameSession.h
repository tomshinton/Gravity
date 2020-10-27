// Gravity Project - Tom Shinton 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/GameSession.h>

#include "GravityGameSession.generated.h"

UCLASS()
class AGravityGameSession : public AGameSession
{
	GENERATED_BODY()

public:

	AGravityGameSession(const FObjectInitializer& ObjectInitialiser);
};
