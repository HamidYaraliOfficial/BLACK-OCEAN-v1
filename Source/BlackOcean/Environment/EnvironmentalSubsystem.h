#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EnvironmentalSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FRegionEnvironmentState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Environment", meta=(ClampMin="0.0", ClampMax="1.0"))
	float PollutionLevel = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Environment")
	float TemperatureAnomalyCelsius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Environment", meta=(ClampMin="0.0", ClampMax="1.0"))
	float WildlifePopulationDensity = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Environment")
	bool bIsProtectedConservationArea = false;
};

// Tracks fictional marine-environment health per region: pollution, ocean
// temperature drift and wildlife population density, all nudged by economic
// decisions (shipping density, industrial activity, conservation spending).
UCLASS()
class UEnvironmentalSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Environment")
	void RegisterRegion(FName RegionId, const FRegionEnvironmentState& InitialState);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Environment")
	void ApplyIndustrialActivity(FName RegionId, float ActivityLevel);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Environment")
	void ApplyConservationEffort(FName RegionId, float EffortLevel);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Environment")
	void DesignateProtectedArea(FName RegionId, bool bProtected);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Environment")
	bool GetRegionState(FName RegionId, FRegionEnvironmentState& OutState) const;

private:
	UPROPERTY()
	TMap<FName, FRegionEnvironmentState> RegionStates;
};
