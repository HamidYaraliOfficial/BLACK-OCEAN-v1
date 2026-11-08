#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SimulationInspectorSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FInspectorEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Inspector")
	FName EntityId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Inspector")
	FString EntityTypeLabel;

	// Free-form key/value snapshot (e.g. "FuelPercent"->"0.62"), populated by
	// whichever subsystem owns the entity. Kept generic so new systems can
	// register inspectable entities without this subsystem knowing about them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Inspector")
	TMap<FString, FString> Fields;
};

// Debug/design-facing inspector: any subsystem can publish a live snapshot of
// an entity (ship, fleet, port, route, contact, weather zone, economy
// entity) here for the Simulation Inspector UI to browse, without those
// systems needing to know about each other or about the UI layer.
UCLASS()
class USimulationInspectorSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Inspector")
	void PublishSnapshot(const FInspectorEntry& Entry);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Inspector")
	bool GetSnapshot(FName EntityId, FInspectorEntry& OutEntry) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Inspector")
	TArray<FName> GetAllTrackedEntityIds() const;

private:
	UPROPERTY()
	TMap<FName, FInspectorEntry> Snapshots;
};
