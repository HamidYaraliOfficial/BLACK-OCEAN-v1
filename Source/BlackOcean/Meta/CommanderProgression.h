#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CommanderProgression.generated.h"

// Player-facing progression. Perks are gameplay-scoped multipliers (never
// direct "win the game" buttons) so difficulty/balance stay meaningful.
USTRUCT(BlueprintType)
struct FCommanderPerks
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Progression", meta=(ClampMin="1.0", ClampMax="1.5"))
	float FleetManagementEfficiency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Progression", meta=(ClampMin="1.0", ClampMax="1.5"))
	float ReconEfficiency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Progression", meta=(ClampMin="1.0", ClampMax="1.5"))
	float LogisticsEfficiency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Progression", meta=(ClampMin="1.0", ClampMax="1.5"))
	float StrategicPlanningBonus = 1.0f;
};

UCLASS()
class UCommanderProgressionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Progression")
	void AddExperience(int32 Amount);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Progression")
	int32 GetCommandLevel() const { return CommandLevel; }

	UFUNCTION(BlueprintPure, Category="BlackOcean|Progression")
	FCommanderPerks GetCurrentPerks() const { return Perks; }

private:
	int32 TotalExperience = 0;
	int32 CommandLevel = 1;
	FCommanderPerks Perks;

	void RecalculateLevel();
};
