#include "CommanderProgression.h"

void UCommanderProgressionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UCommanderProgressionSubsystem::AddExperience(int32 Amount)
{
	TotalExperience += FMath::Max(0, Amount);
	RecalculateLevel();
}

void UCommanderProgressionSubsystem::RecalculateLevel()
{
	// Simple square-root curve: each level requires progressively more XP.
	CommandLevel = FMath::Max(1, FMath::FloorToInt(FMath::Sqrt(static_cast<float>(TotalExperience) / 100.0f)) + 1);

	const float LevelBonus = FMath::Min(0.5f, (CommandLevel - 1) * 0.02f);
	Perks.FleetManagementEfficiency = 1.0f + LevelBonus;
	Perks.ReconEfficiency = 1.0f + LevelBonus;
	Perks.LogisticsEfficiency = 1.0f + LevelBonus;
	Perks.StrategicPlanningBonus = 1.0f + LevelBonus;
}
