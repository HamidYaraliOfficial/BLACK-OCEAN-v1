#include "SimulationInspectorSubsystem.h"

void USimulationInspectorSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USimulationInspectorSubsystem::PublishSnapshot(const FInspectorEntry& Entry)
{
	Snapshots.Add(Entry.EntityId, Entry);
}

bool USimulationInspectorSubsystem::GetSnapshot(FName EntityId, FInspectorEntry& OutEntry) const
{
	if (const FInspectorEntry* Found = Snapshots.Find(EntityId))
	{
		OutEntry = *Found;
		return true;
	}
	return false;
}

TArray<FName> USimulationInspectorSubsystem::GetAllTrackedEntityIds() const
{
	TArray<FName> Ids;
	Snapshots.GetKeys(Ids);
	return Ids;
}
