// Gravity Project - Tom Shinton 2020

#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/GameModeBase.h>

#include "GravityGameModeBase.generated.h"

UCLASS()
class AGravityGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AGravityGameModeBase();

	//AGameMode
	virtual TSubclassOf<AGameSession> GetGameSessionClass() const override;
	//~AGameMode
};
