#include "FleetChronicleSubsystem.h"

void UFleetChronicleSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFleetChronicleSubsystem::AddEntry(const FChronicleEntry& Entry)
{
	Entries.Add(Entry);
}

TArray<FChronicleEntry> UFleetChronicleSubsystem::GetEntriesForSubject(FName SubjectId) const
{
	TArray<FChronicleEntry> Result;
	for (const FChronicleEntry& Entry : Entries)
	{
		if (Entry.SubjectId == SubjectId)
		{
			Result.Add(Entry);
		}
	}
	return Result;
}
