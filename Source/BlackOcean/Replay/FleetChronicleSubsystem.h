#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BlackOceanTypes.h"
#include "FleetChronicleSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FChronicleEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Chronicle")
	FGameTimestamp Timestamp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Chronicle")
	FName SubjectId; // Fleet, ship, port, captain or mission id.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Chronicle")
	FText Summary;
};

// Long-term, human-readable campaign history (distinct from the low-level
// UReplayRecorderSubsystem event stream): the entries a player actually
// wants to scroll through in the Fleet Chronicle UI to remember "what
// happened to this ship/captain/port over the campaign".
UCLASS()
class UFleetChronicleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Chronicle")
	void AddEntry(const FChronicleEntry& Entry);

	UFUNCTION(BlueprintPure, Category="BlackOcean|Chronicle")
	TArray<FChronicleEntry> GetEntriesForSubject(FName SubjectId) const;

	UFUNCTION(BlueprintPure, Category="BlackOcean|Chronicle")
	TArray<FChronicleEntry> GetFullChronicle() const { return Entries; }

private:
	UPROPERTY()
	TArray<FChronicleEntry> Entries;
};
