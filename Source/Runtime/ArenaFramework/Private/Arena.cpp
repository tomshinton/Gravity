#include "Runtime/ArenaFramework/Public/Arena.h"

#include <Runtime/Engine/Classes/Components/BoxComponent.h>
#include <Runtime/Engine/Classes/Components/SceneComponent.h>

namespace ArenaPrivate
{
	const FName RootComponentName = TEXT("ArenaRoot");
	const FName TopBoundName = TEXT("TopBound");
	const FName BottomBound = TEXT("BottomBound");
	const FName RightBound = TEXT("RightBound");
	const FName LeftBound = TEXT("LeftBound");
}

AArena::AArena(const FObjectInitializer& ObjectInitialiser) 
	: Super(ObjectInitialiser)
	, ArenaWidth(1000.f)
	, ArenaHeight(500.f)
	, BoundWidth(20.f)
	, ArenaDepth(1000.f)
	, Root(ObjectInitialiser.CreateDefaultSubobject<USceneComponent>(this, ArenaPrivate::RootComponentName))
	, TopBound(ObjectInitialiser.CreateDefaultSubobject<UBoxComponent>(this, ArenaPrivate::TopBoundName))
	, BottomBound(ObjectInitialiser.CreateDefaultSubobject<UBoxComponent>(this, ArenaPrivate::BottomBound))
	, RightBound(ObjectInitialiser.CreateDefaultSubobject<UBoxComponent>(this, ArenaPrivate::RightBound))
	, LeftBound(ObjectInitialiser.CreateDefaultSubobject<UBoxComponent>(this, ArenaPrivate::LeftBound))
{
	SetRootComponent(Root);

	TopBound->SetupAttachment(Root);
	BottomBound->SetupAttachment(Root);
	RightBound->SetupAttachment(Root);
	LeftBound->SetupAttachment(Root);
}

void AArena::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const float BoundWidthExtent = BoundWidth * 0.5f;
	const float WidthExtent = (ArenaWidth * 0.5f) - BoundWidthExtent;
	const float HeightExtent = (ArenaHeight * 0.5f) - BoundWidthExtent;

	TopBound->SetBoxExtent(FVector(ArenaDepth, WidthExtent, BoundWidthExtent));
	BottomBound->SetBoxExtent(FVector(ArenaDepth, WidthExtent, BoundWidthExtent));
	RightBound->SetBoxExtent(FVector(ArenaDepth, BoundWidth * 0.5f, HeightExtent));
	LeftBound->SetBoxExtent(FVector(ArenaDepth, BoundWidth * 0.5f, HeightExtent));

	TopBound->SetRelativeLocation(FVector(0.f, 0.f, HeightExtent + BoundWidthExtent));
	BottomBound->SetRelativeLocation(FVector(0.f, 0.f, -(HeightExtent + BoundWidthExtent)));

	RightBound->SetRelativeLocation(FVector(0.f, WidthExtent + BoundWidthExtent, 0.f));
	LeftBound->SetRelativeLocation(FVector(0.f, -(WidthExtent + BoundWidthExtent), 0.f));
}
