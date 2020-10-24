#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/Camera/CameraActor.h>

#include "GravityCamera.generated.h"

UCLASS()
class CAMERA_API AGravityCamera : public ACameraActor
{
	GENERATED_BODY()

public:

	AGravityCamera(const FObjectInitializer& ObjectInitialiser);

	static AGravityCamera* Get(UObject& InWorldContext);
};