#pragma once

#include <Runtime/Engine/Classes/Components/BoxComponent.h>

#include "ArenaBounds.generated.h"

class AArena;

UCLASS(Within=Arena)
class UArenaBounds : public UBoxComponent
{
	GENERATED_BODY()

	UArenaBounds();

public:

	//UPrimitiveComponent
	void BeginPlay() override;
	//~UPrimitiveComponent

	void NotifyOfInboundActor(const AActor& InNewInboundActor);
	void Initialise(UArenaBounds& InBound, const FVector& InWrapOffset);

private:

	UPROPERTY()
	TArray<const AActor*> InboundActors;

	UPROPERTY()
	UArenaBounds* AssociatedBound;

	FVector WrapOffset;
	float WrapPadding;

	UFUNCTION()
	void OnBoundsLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};