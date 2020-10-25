#pragma once

#include <Runtime/Engine/Classes/Components/ActorComponent.h>

#include "GravityMovementComponent.generated.h"

class UPrimitiveComponent;

USTRUCT()
struct FImpulsePacket
{
	GENERATED_BODY()

public:

	FImpulsePacket()
		: UpStrength(0.f)
		, RightStrength(0.f)
		, Tolerance(.1f)
	{};

#if !UE_BUILD_SHIPPING
	FString ToString() const 
	{
		return FString::Printf(TEXT("Up: %f, Right: %f"), UpStrength, RightStrength);
	}
#endif //!UE_BUILD_SHIPPING

	bool operator==(const FImpulsePacket& InOtherPacket) const
	{
		return IsPacketWithinTolerance(InOtherPacket);
	}

	bool operator!=(const FImpulsePacket& InOtherPacket) const
	{
		return !IsPacketWithinTolerance(InOtherPacket);
	}

	bool IsPacketWithinTolerance(const FImpulsePacket& InPacket) const
	{
		return
			FMath::IsNearlyEqual(UpStrength, InPacket.UpStrength, Tolerance) &&
			FMath::IsNearlyEqual(RightStrength, InPacket.RightStrength, Tolerance);
	}

	UPROPERTY()
	float UpStrength;

	UPROPERTY()
	float RightStrength;

	float Tolerance;
};

UCLASS()
class MOVEMENT_API UGravityMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UGravityMovementComponent();

	void BeginPlay() override;

	void SetupComponentInputBindings(UInputComponent& PlayerInputComponent) override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY(EditDefaultsOnly)
	float MoveSpeed;

private:

#if WITH_CLIENT_CODE
	void TickClient(const float InDeltaTime);
	void MoveUp(const float InStrength);
	void MoveRight(const float InStrenth);
#endif //WITH_CLIENT_CODE

#if WITH_SERVER_CODE
	void TickServer(const float InDeltaTime);
#endif WITH_SERVER_CODE

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetImpulsePacket(const FImpulsePacket& InPacket);
	void Server_SetImpulsePacket_Implementation(const FImpulsePacket& InPacket);
	bool Server_SetImpulsePacket_Validate(const FImpulsePacket& InPacket) { return true; };

	UPROPERTY(Transient)
	UPrimitiveComponent* OwningPhysicsRoot;

	FImpulsePacket CurrImpulsePacket;
	FImpulsePacket LastImpulsePacket;
};