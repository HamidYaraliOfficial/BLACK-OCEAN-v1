#include "PerformanceProfilerSubsystem.h"

void UPerformanceProfilerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPerformanceProfilerSubsystem::ReportCostMs(EProfiledCostCategory Category, float Milliseconds)
{
	LastCosts.Add(Category, FMath::Max(0.0f, Milliseconds));
}

float UPerformanceProfilerSubsystem::GetLastReportedCostMs(EProfiledCostCategory Category) const
{
	const float* Cost = LastCosts.Find(Category);
	return Cost ? *Cost : 0.0f;
}

float UPerformanceProfilerSubsystem::GetTotalSimulationCostMs() const
{
	float Total = 0.0f;
	for (const auto& Pair : LastCosts)
	{
		Total += Pair.Value;
	}
	return Total;
}
