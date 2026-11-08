#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AchievementsSubsystem.generated.h"

UENUM(BlueprintType)
enum class EAchievementCategory : uint8
{
	Fleet, Exploration, Research, Rescue, Logistics, PortDevelopment, CampaignCompletion
};

USTRUCT(BlueprintType)
struct FAchievementDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Achievements")
	FName AchievementId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Achievements")
	EAchievementCategory Category = EAchievementCategory::Fleet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Achievements")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Achievements")
	FText Description;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="BlackOcean|Achievements")
	bool bUnlocked = false;
};

UCLASS()
class UAchievementsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Achievements")
	void RegisterAchievement(const FAchievementDefinition& Definition);

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Achievements")
	bool Unlock(FName AchievementId);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Achievements")
	bool IsUnlocked(FName AchievementId) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Achievements")
	TArray<FName> GetUnlockedAchievements() const;

private:
	UPROPERTY()
	TMap<FName, FAchievementDefinition> Achievements;
};
