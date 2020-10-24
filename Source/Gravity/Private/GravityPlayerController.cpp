// Gravity Project - Tom Shinton 2020

#include "Gravity/Public/GravityPlayerController.h"

#include <Runtime/Camera/Public/GravityCamera.h>

#if !UE_BUILD_SHIPPING
#include "Gravity/Public/GravityCheatManager.h"
#endif //!UE_BUILD_SHIPPING

AGravityPlayerController::AGravityPlayerController(const FObjectInitializer& ObjectInititaliser)
{
#if !UE_BUILD_SHIPPING
	CheatClass = UGravityCheatManager::StaticClass();
#endif //!UE_BUILD_SHIPPING

	SetReplicates(true);
}

void AGravityPlayerController::BeginPlay()
{
	Super::BeginPlay();

#if !UE_BUILD_SHIPPING
	EnableCheats();
#endif //!UE_BUILD_SHIPPING
}

void AGravityPlayerController::AutoManageActiveCameraTarget(AActor* SuggestedTarget)
{
	if (AGravityCamera* Camera = AGravityCamera::Get(*this))
	{
		SetViewTarget(Camera);
	}
}
