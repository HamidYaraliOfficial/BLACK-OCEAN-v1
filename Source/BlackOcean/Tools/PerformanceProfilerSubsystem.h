#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PerformanceProfilerSubsystem.generated.h"

UENUM(BlueprintType)
enum class EProfiledCostCategory : uint8
{
	AI, Physics, Ocean, Streaming, Simulation, Network, Rendering
};

// Lightweight cost tracker: subsystems report how many milliseconds they
// spent this frame/tick, and the Performance Profiler UI reads it back.
// Real GPU/CPU/memory numbers still come from Unreal's own stat system;
// this exists specifically for BLACK OCEAN's own simulation-cost categories
// (AI cost, Ocean cost, Streaming cost, Simulation tick time, Network cost)
// called out in the design spec, which stat commands don't label as such.
UCLASS()
class UPerformanceProfilerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Performance")
	void ReportCostMs(EProfiledCostCategory Category, float Milliseconds);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Performance")
	float GetLastReportedCostMs(EProfiledCostCategory Category) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Performance")
	float GetTotalSimulationCostMs() const;

private:
	TMap<EProfiledCostCategory, float> LastCosts;
};
