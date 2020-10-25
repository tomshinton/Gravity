#pragma once

#include <Runtime/Core/Public/CoreMinimal.h>
#include <Runtime/Engine/Classes/GameFramework/Actor.h>

#include "Arena.generated.h"

class UBoxComponent;
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

private:
	
	void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TopBound;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BottomBound;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* RightBound;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* LeftBound;
};