#include "AdmiraltyCommandCenter.h"

UAdmiraltyCommandCenter::UAdmiraltyCommandCenter()
{
	PrimaryComponentTick.bCanEverTick = false;

	const EAdmiraltyFacility AllFacilities[] = {
		EAdmiraltyFacility::OperationsRoom, EAdmiraltyFacility::FleetManagement,
		EAdmiraltyFacility::Shipyard, EAdmiraltyFacility::ResearchCenter,
		EAdmiraltyFacility::IntelligenceCenter, EAdmiraltyFacility::Logistics,
		EAdmiraltyFacility::Diplomacy, EAdmiraltyFacility::PortManagement,
		EAdmiraltyFacility::BriefingRoom
	};
	for (EAdmiraltyFacility Facility : AllFacilities)
	{
		Facilities.Add(Facility, FFacilityUpgradeLevel());
	}
}

bool UAdmiraltyCommandCenter::UpgradeFacility(EAdmiraltyFacility Facility)
{
	FFacilityUpgradeLevel* Upgrade = Facilities.Find(Facility);
	if (!Upgrade || Upgrade->Level >= Upgrade->MaxLevel)
	{
		return false;
	}
	Upgrade->Level++;
	return true;
}

float UAdmiraltyCommandCenter::GetFacilityEffectMultiplier(EAdmiraltyFacility Facility) const
{
	const FFacilityUpgradeLevel* Upgrade = Facilities.Find(Facility);
	return Upgrade ? Upgrade->GetEffectMultiplier() : 1.0f;
}
