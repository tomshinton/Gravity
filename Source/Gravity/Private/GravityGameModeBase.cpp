// Gravity Project - Tom Shinton 2020

#include "Gravity/Public/GravityGameModeBase.h"

#include "Gravity/Public/GravityGameSession.h"
#include "Gravity/Public/GravityPawn.h"
#include "Gravity/Public/GravityPlayerController.h"

AGravityGameModeBase::AGravityGameModeBase()
{
	DefaultPawnClass = AGravityPawn::StaticClass();
	PlayerControllerClass = AGravityPlayerController::StaticClass();
}

TSubclassOf<AGameSession> AGravityGameModeBase::GetGameSessionClass() const
{ 
	return AGravityGameSession::StaticClass();
}
