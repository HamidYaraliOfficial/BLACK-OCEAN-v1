#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdmiraltyCommandCenter.generated.h"

UENUM(BlueprintType)
enum class EAdmiraltyFacility : uint8
{
	OperationsRoom, FleetManagement, Shipyard, ResearchCenter,
	IntelligenceCenter, Logistics, Diplomacy, PortManagement, BriefingRoom
};

USTRUCT(BlueprintType)
struct FFacilityUpgradeLevel
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Admiralty")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Admiralty")
	int32 MaxLevel = 5;

	// Generic effect multiplier this facility grants at its current level to
	// whichever subsystem it governs (e.g. ResearchCenter -> research speed).
	float GetEffectMultiplier() const
	{
		return 1.0f + (Level - 1) * 0.15f;
	}
};

// The player's home base: a set of upgradeable facilities whose levels feed
// real multipliers into Research, Fleet, Shipyard, Diplomacy and Logistics.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UAdmiraltyCommandCenter : public UActorComponent
{
	GENERATED_BODY()

public:
	UAdmiraltyCommandCenter();

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Admiralty")
	bool UpgradeFacility(EAdmiraltyFacility Facility);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Admiralty")
	float GetFacilityEffectMultiplier(EAdmiraltyFacility Facility) const;

private:
	UPROPERTY(VisibleAnywhere, Category="BlackOcean|Admiralty")
	TMap<EAdmiraltyFacility, FFacilityUpgradeLevel> Facilities;
};
