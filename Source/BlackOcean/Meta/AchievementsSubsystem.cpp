#include "AchievementsSubsystem.h"

void UAchievementsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UAchievementsSubsystem::RegisterAchievement(const FAchievementDefinition& Definition)
{
	Achievements.Add(Definition.AchievementId, Definition);
}

bool UAchievementsSubsystem::Unlock(FName AchievementId)
{
	if (FAchievementDefinition* Achievement = Achievements.Find(AchievementId))
	{
		if (!Achievement->bUnlocked)
		{
			Achievement->bUnlocked = true;
			return true;
		}
	}
	return false;
}

bool UAchievementsSubsystem::IsUnlocked(FName AchievementId) const
{
	const FAchievementDefinition* Achievement = Achievements.Find(AchievementId);
	return Achievement && Achievement->bUnlocked;
}

TArray<FName> UAchievementsSubsystem::GetUnlockedAchievements() const
{
	TArray<FName> Result;
	for (const auto& Pair : Achievements)
	{
		if (Pair.Value.bUnlocked) Result.Add(Pair.Key);
	}
	return Result;
}
