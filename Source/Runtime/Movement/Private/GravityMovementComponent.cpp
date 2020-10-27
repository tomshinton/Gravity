#include "Runtime/Movement/Public/GravityMovementComponent.h"

#include <Runtime/Engine/Classes/Components/PrimitiveComponent.h>
#include <Runtime/Engine/Public/Net/UnrealNetwork.h>

DEFINE_LOG_CATEGORY_STATIC(GravityMovementComponentLog, Log, Log)

namespace GravityMovementComponentBindings
{
	const FName MoveUpBinding = TEXT("MoveUp");
	const FName MoveRightBinding = TEXT("MoveRight");
}

UGravityMovementComponent::UGravityMovementComponent()
	: MoveSpeed(1.f)
	, OwningPhysicsRoot(nullptr)
	, CurrImpulsePacket()
	, LastImpulsePacket()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	bReplicates = true;
}

void UGravityMovementComponent::BeginPlay()
{
	Super::BeginPlay();

#if WITH_SERVER_CODE
	if (GetOwner()->HasAuthority())
	{
		if (UPrimitiveComponent* OwnerRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()))
		{
			OwnerRoot->SetSimulatePhysics(true);
			OwnerRoot->SetEnableGravity(true);

			OwningPhysicsRoot = OwnerRoot;
		}
		else
		{
			UE_LOG(GravityMovementComponentLog, Error, TEXT("Cannot enable physics - owning actor doesnt have a primitive component as its root"));
		}
	}
#endif //WITH_SERVER_CODE
}

#if WITH_CLIENT_CODE
void UGravityMovementComponent::SetupComponentInputBindings(UInputComponent& PlayerInputComponent)
{
	Super::SetupComponentInputBindings(PlayerInputComponent);
	
	PlayerInputComponent.BindAxis(GravityMovementComponentBindings::MoveUpBinding, this, &UGravityMovementComponent::MoveUp);
	PlayerInputComponent.BindAxis(GravityMovementComponentBindings::MoveRightBinding, this, &UGravityMovementComponent::MoveRight);
}
#endif //WITH_CLIENT_CODE

void UGravityMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

#if WITH_CLIENT_CODE
	if (GetNetMode() != NM_DedicatedServer)
	{
		TickClient(DeltaTime);
	}
#endif //WITH_CLIENT_CODE

#if WITH_SERVER_CODE
	if (GetOwner()->HasAuthority())
	{
		TickServer(DeltaTime);
	}
#endif //WITH_SERVER_CODE
}

#if WITH_CLIENT_CODE
void UGravityMovementComponent::TickClient(const float InDeltaTime)
{
	if (CurrImpulsePacket != LastImpulsePacket)
	{
		Server_SetImpulsePacket(CurrImpulsePacket);
		LastImpulsePacket = CurrImpulsePacket;
	}
}
#endif //WITH_CLIENT_CODE

#if WITH_SERVER_CODE
void UGravityMovementComponent::TickServer(const float InDeltaTime)
{
	GEngine->AddOnScreenDebugMessage(1, 1, FColor::White, FString::Printf(TEXT("Location: %s"), *GetOwner()->GetActorLocation().ToString()));
	GEngine->AddOnScreenDebugMessage(2, 1, FColor::White, FString::Printf(TEXT("Last Impulse: %s"), *LastImpulsePacket.ToString()));

	if (OwningPhysicsRoot != nullptr)
	{
		OwningPhysicsRoot->AddImpulse(FVector::UpVector * ((LastImpulsePacket.UpStrength * MoveSpeed) * InDeltaTime), NAME_None, true);
		OwningPhysicsRoot->AddImpulse(FVector::RightVector * ((LastImpulsePacket.RightStrength * MoveSpeed) * InDeltaTime), NAME_None, true);
	}
}
#endif //WITH_SERVER_CODE

void UGravityMovementComponent::Server_SetImpulsePacket_Implementation(const FImpulsePacket& InPacket)
{
	LastImpulsePacket = InPacket;
}

#if WITH_CLIENT_CODE
void UGravityMovementComponent::MoveUp(const float InStrength)
{
	CurrImpulsePacket.UpStrength = InStrength;
}
#endif //WITH_CLIENT_CODE

#if WITH_CLIENT_CODE
void UGravityMovementComponent::MoveRight(const float InStrenth)
{
	CurrImpulsePacket.RightStrength = InStrenth;
}
#endif //WITH_CLIENT_CODE
