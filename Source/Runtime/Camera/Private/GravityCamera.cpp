#pragma once

#include "Runtime/Camera/Public/GravityCamera.h"

#include <Runtime/Engine/Public/EngineUtils.h>

AGravityCamera::AGravityCamera(const FObjectInitializer& ObjectInitialiser)
	: Super(ObjectInitialiser)
{

}

AGravityCamera* AGravityCamera::Get(UObject& InWorldContext)
{
	if (UWorld* World = InWorldContext.GetWorld())
	{
		for (TActorIterator<AGravityCamera> Itr(World); Itr; ++Itr)
		{
			if (AGravityCamera* Camera = *Itr)
			{
				return Camera;
			}
		}
	}

	return nullptr;
}
