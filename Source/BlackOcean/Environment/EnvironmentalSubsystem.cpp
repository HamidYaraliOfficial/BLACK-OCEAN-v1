#include "EnvironmentalSubsystem.h"

void UEnvironmentalSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEnvironmentalSubsystem::RegisterRegion(FName RegionId, const FRegionEnvironmentState& InitialState)
{
	RegionStates.Add(RegionId, InitialState);
}

void UEnvironmentalSubsystem::ApplyIndustrialActivity(FName RegionId, float ActivityLevel)
{
	FRegionEnvironmentState& State = RegionStates.FindOrAdd(RegionId);
	if (State.bIsProtectedConservationArea)
	{
		ActivityLevel *= 0.2f; // Protected areas heavily restrict industrial impact.
	}
	State.PollutionLevel = FMath::Clamp(State.PollutionLevel + ActivityLevel * 0.05f, 0.0f, 1.0f);
	State.WildlifePopulationDensity = FMath::Clamp(State.WildlifePopulationDensity - ActivityLevel * 0.02f, 0.0f, 1.0f);
}

void UEnvironmentalSubsystem::ApplyConservationEffort(FName RegionId, float EffortLevel)
{
	FRegionEnvironmentState& State = RegionStates.FindOrAdd(RegionId);
	State.PollutionLevel = FMath::Clamp(State.PollutionLevel - EffortLevel * 0.04f, 0.0f, 1.0f);
	State.WildlifePopulationDensity = FMath::Clamp(State.WildlifePopulationDensity + EffortLevel * 0.03f, 0.0f, 1.0f);
}

void UEnvironmentalSubsystem::DesignateProtectedArea(FName RegionId, bool bProtected)
{
	FRegionEnvironmentState& State = RegionStates.FindOrAdd(RegionId);
	State.bIsProtectedConservationArea = bProtected;
}

bool UEnvironmentalSubsystem::GetRegionState(FName RegionId, FRegionEnvironmentState& OutState) const
{
	if (const FRegionEnvironmentState* Found = RegionStates.Find(RegionId))
	{
		OutState = *Found;
		return true;
	}
	return false;
}
