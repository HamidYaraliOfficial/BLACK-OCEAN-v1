#include "GlobalMarketSubsystem.h"

void UGlobalMarketSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGlobalMarketSubsystem::SetBasePrice(EStrategicResource Resource, float PricePerUnit)
{
	CurrentPrices.Add(Resource, FMath::Max(0.01f, PricePerUnit));
}

void UGlobalMarketSubsystem::UpdatePriceFromSupplyDemand(EStrategicResource Resource, float SupplyVolume, float DemandVolume)
{
	float& Price = CurrentPrices.FindOrAdd(Resource, 1.0f);
	if (SupplyVolume <= 0.0f)
	{
		Price *= 1.05f; // Shortage: price rises.
		return;
	}
	const float Ratio = DemandVolume / SupplyVolume;
	// Smoothly nudge price toward the supply/demand ratio rather than
	// snapping, so markets feel gradual rather than jumpy.
	Price = FMath::Lerp(Price, Price * FMath::Clamp(Ratio, 0.5f, 2.0f), 0.15f);
	Price = FMath::Clamp(Price, 0.01f, 1000.0f);
}

void UGlobalMarketSubsystem::ApplyDisruption(EStrategicResource Resource, float PriceShockPercent)
{
	float& Price = CurrentPrices.FindOrAdd(Resource, 1.0f);
	Price = FMath::Clamp(Price * (1.0f + PriceShockPercent), 0.01f, 1000.0f);
}

float UGlobalMarketSubsystem::GetCurrentPrice(EStrategicResource Resource) const
{
	const float* Price = CurrentPrices.Find(Resource);
	return Price ? *Price : 1.0f;
}
