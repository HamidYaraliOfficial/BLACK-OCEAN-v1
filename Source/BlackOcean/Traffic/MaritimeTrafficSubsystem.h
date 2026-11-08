#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MaritimeTrafficSubsystem.generated.h"

UENUM(BlueprintType)
enum class ECivilianVesselType : uint8
{
	CargoVessel, Ferry, FishingVessel, ResearchShip, SupportVessel
};

USTRUCT(BlueprintType)
struct FTradeRoute
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Traffic")
	FName RouteId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Traffic")
	FName OriginPortId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Traffic")
	FName DestinationPortId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Traffic", meta=(ClampMin="0.0", ClampMax="1.0"))
	float SecurityLevel = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Traffic")
	int32 ActiveVesselCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Traffic")
	float BaseTradeValuePerDay = 100.0f;

	// Economic contribution this tick, reduced when security is low or a
	// Dynamic Maritime Threat Engine event has interrupted the route.
	float GetEffectiveTradeValue(bool bIsInterrupted) const
	{
		if (bIsInterrupted) return 0.0f;
		return BaseTradeValuePerDay * FMath::Clamp(SecurityLevel, 0.1f, 1.0f);
	}
};

// Simulates background civilian sea traffic (cargo, ferries, fishing,
// research and support vessels) travelling fixed trade routes between
// fictional ports. Density/health of these routes feeds the Trade Flow
// Visualization and the Economy subsystem's trade income.
UCLASS()
class UMaritimeTrafficSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Traffic")
	void RegisterRoute(const FTradeRoute& Route);

	// Traffic density rises with time-of-day/economy and falls in storms or
	// high-threat regions; DensityFactor in [0,1] comes from Ocean/Economy.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Traffic")
	void UpdateRouteDensity(FName RouteId, float DensityFactor, int32 MaxVesselsOnRoute);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Traffic")
	void SetRouteInterrupted(FName RouteId, bool bInterrupted);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Traffic")
	float GetTotalDailyTradeValue() const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Traffic")
	TArray<FName> GetAllRouteIds() const;

private:
	UPROPERTY()
	TMap<FName, FTradeRoute> Routes;

	TSet<FName> InterruptedRoutes;
};
