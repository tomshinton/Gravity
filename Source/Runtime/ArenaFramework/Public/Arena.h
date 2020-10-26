#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>

#include "Arena.generated.h"

class UArenaBounds;
class USceneComponent;

UCLASS()
class AArena : public AActor
{
	GENERATED_BODY()
	
public:

	AArena(const FObjectInitializer& ObjectInitialiser);

	UPROPERTY(EditAnywhere)
	float ArenaWidth;

	UPROPERTY(EditAnywhere)
	float ArenaHeight;

	UPROPERTY(EditAnywhere)
	float BoundWidth;

	UPROPERTY(EditAnywhere)
	float ArenaDepth;

	UPROPERTY(EditAnywhere)
	float TeleportPadding;

private:

	//AActor
	void OnConstruction(const FTransform& Transform) override;
	void PostInitializeComponents() override;
	//~AActor

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY()
	UArenaBounds* TopBound;

	UPROPERTY()
	UArenaBounds* BottomBound;

	UPROPERTY()
	UArenaBounds* RightBound;

	UPROPERTY()
	UArenaBounds* LeftBound;
};