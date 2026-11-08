#include "MaritimeTrafficSubsystem.h"

void UMaritimeTrafficSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMaritimeTrafficSubsystem::RegisterRoute(const FTradeRoute& Route)
{
	Routes.Add(Route.RouteId, Route);
}

void UMaritimeTrafficSubsystem::UpdateRouteDensity(FName RouteId, float DensityFactor, int32 MaxVesselsOnRoute)
{
	if (FTradeRoute* Route = Routes.Find(RouteId))
	{
		Route->ActiveVesselCount = FMath::RoundToInt(FMath::Clamp(DensityFactor, 0.0f, 1.0f) * MaxVesselsOnRoute);
	}
}

void UMaritimeTrafficSubsystem::SetRouteInterrupted(FName RouteId, bool bInterrupted)
{
	if (bInterrupted) InterruptedRoutes.Add(RouteId);
	else InterruptedRoutes.Remove(RouteId);
}

float UMaritimeTrafficSubsystem::GetTotalDailyTradeValue() const
{
	float Total = 0.0f;
	for (const auto& Pair : Routes)
	{
		Total += Pair.Value.GetEffectiveTradeValue(InterruptedRoutes.Contains(Pair.Key));
	}
	return Total;
}

TArray<FName> UMaritimeTrafficSubsystem::GetAllRouteIds() const
{
	TArray<FName> Ids;
	Routes.GetKeys(Ids);
	return Ids;
}
