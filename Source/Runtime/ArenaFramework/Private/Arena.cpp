#include "Runtime/ArenaFramework/Public/Arena.h"
#include "Runtime/ArenaFramework/Public/ArenaBounds.h"

#include <Runtime/Engine/Classes/Components/SceneComponent.h>

namespace ArenaPrivate
{
	const FName RootComponentName = TEXT("ArenaRoot");
	const FName TopBoundName = TEXT("TopBound");
	const FName BottomBound = TEXT("BottomBound");
	const FName RightBound = TEXT("RightBound");
	const FName LeftBound = TEXT("LeftBound");

	const FName ArenaBoundsCollisionProfile = TEXT("ArenaBounds");
}

AArena::AArena(const FObjectInitializer& ObjectInitialiser) 
	: Super(ObjectInitialiser)
	, ArenaWidth(1000.f)
	, ArenaHeight(500.f)
	, BoundWidth(20.f)
	, ArenaDepth(1000.f)
	, TeleportPadding(BoundWidth + 20.f)
	, Root(ObjectInitialiser.CreateDefaultSubobject<USceneComponent>(this, ArenaPrivate::RootComponentName))
	, TopBound(ObjectInitialiser.CreateDefaultSubobject<UArenaBounds>(this, ArenaPrivate::TopBoundName))
	, BottomBound(ObjectInitialiser.CreateDefaultSubobject<UArenaBounds>(this, ArenaPrivate::BottomBound))
	, RightBound(ObjectInitialiser.CreateDefaultSubobject<UArenaBounds>(this, ArenaPrivate::RightBound))
	, LeftBound(ObjectInitialiser.CreateDefaultSubobject<UArenaBounds>(this, ArenaPrivate::LeftBound))
{
	SetRootComponent(Root);

	TopBound->SetupAttachment(Root);
	BottomBound->SetupAttachment(Root);
	RightBound->SetupAttachment(Root);
	LeftBound->SetupAttachment(Root);

	TopBound->SetCollisionProfileName(ArenaPrivate::ArenaBoundsCollisionProfile);
	BottomBound->SetCollisionProfileName(ArenaPrivate::ArenaBoundsCollisionProfile);
	RightBound->SetCollisionProfileName(ArenaPrivate::ArenaBoundsCollisionProfile);
	LeftBound->SetCollisionProfileName(ArenaPrivate::ArenaBoundsCollisionProfile);
}

void AArena::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	TopBound->Initialise(*BottomBound, FVector(0.f, 0.f, -ArenaHeight));
	BottomBound->Initialise(*TopBound, FVector(0.f, 0.f, ArenaHeight));
	RightBound->Initialise(*LeftBound, FVector(0.f, -ArenaWidth, 0.f));
	LeftBound->Initialise(*RightBound, FVector(0.f, ArenaWidth, 0.f));
}

void AArena::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const float BoundWidthExtent = BoundWidth * 0.5f;
	const float WidthExtent = (ArenaWidth * 0.5f) - BoundWidthExtent;
	const float HeightExtent = (ArenaHeight * 0.5f) - BoundWidthExtent;

	TopBound->SetBoxExtent(FVector(ArenaDepth, WidthExtent + BoundWidth, BoundWidthExtent));
	TopBound->SetRelativeLocation(FVector(0.f, 0.f, HeightExtent + BoundWidthExtent));

	BottomBound->SetBoxExtent(FVector(ArenaDepth, WidthExtent + BoundWidth, BoundWidthExtent));	
	BottomBound->SetRelativeLocation(FVector(0.f, 0.f, -(HeightExtent + BoundWidthExtent)));

	RightBound->SetBoxExtent(FVector(ArenaDepth, BoundWidth * 0.5f, HeightExtent));
	RightBound->SetRelativeLocation(FVector(0.f, WidthExtent + BoundWidthExtent, 0.f));

	LeftBound->SetBoxExtent(FVector(ArenaDepth, BoundWidth * 0.5f, HeightExtent));
	LeftBound->SetRelativeLocation(FVector(0.f, -(WidthExtent + BoundWidthExtent), 0.f));	
}