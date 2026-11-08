#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EconomySubsystem.h"
#include "GlobalMarketSubsystem.generated.h"

// Fictional cross-faction commodity market: prices drift with supply/demand,
// storms, port capacity and production, giving Economic AI and the player
// something to actually trade against rather than fixed prices.
UCLASS()
class UGlobalMarketSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	void SetBasePrice(EStrategicResource Resource, float PricePerUnit);

	// Shifts price toward higher values when demand exceeds supply and vice
	// versa; call once per campaign day with each side's aggregate volume.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	void UpdatePriceFromSupplyDemand(EStrategicResource Resource, float SupplyVolume, float DemandVolume);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Economy")
	void ApplyDisruption(EStrategicResource Resource, float PriceShockPercent);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Economy")
	float GetCurrentPrice(EStrategicResource Resource) const;

private:
	TMap<EStrategicResource, float> CurrentPrices;
};
