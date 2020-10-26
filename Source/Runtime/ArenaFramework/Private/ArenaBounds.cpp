#include "Runtime/ArenaFramework/Public/ArenaBounds.h"
#include "Runtime/ArenaFramework/Public/Arena.h"

UArenaBounds::UArenaBounds()
	: WrapOffset(FVector::ZeroVector)
	, WrapPadding(1.1f)
{
	LineThickness = 10.f;
}

void UArenaBounds::BeginPlay()
{
	Super::BeginPlay();

#if WITH_SERVER_CODE
	if (AArena* Arena = GetOwner<AArena>())
	{
		if (Arena->HasAuthority())
		{
			OnComponentEndOverlap.AddDynamic(this, &UArenaBounds::OnBoundsLeft);
		}
	}
#endif //WITH_SERVER_CODE
}

void UArenaBounds::NotifyOfInboundActor(const AActor& InNewInboundActor)
{
	InboundActors.Add(&InNewInboundActor);
}

void UArenaBounds::Initialise(UArenaBounds& InBound, const FVector& InWrapOffset)
{
	AssociatedBound = &InBound;
	WrapOffset = InWrapOffset * WrapPadding;
}
	
void UArenaBounds::OnBoundsLeft(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!InboundActors.Contains(OtherActor))
	{
		AssociatedBound->NotifyOfInboundActor(*OtherActor);
		OtherActor->SetActorLocation(OtherActor->GetActorLocation() + WrapOffset);
	}
	else
	{
		InboundActors.Remove(OtherActor);
	}
}
