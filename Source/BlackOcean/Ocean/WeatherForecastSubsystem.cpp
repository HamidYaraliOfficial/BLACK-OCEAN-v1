#include "WeatherForecastSubsystem.h"

void UWeatherForecastSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FWeatherForecast UWeatherForecastSubsystem::GenerateForecast(const FOceanRegionState& CurrentState, int32 LeadTimeHours, float ForecastTechnologyLevel) const
{
	FWeatherForecast Forecast;
	Forecast.RegionId = CurrentState.RegionId;
	Forecast.LeadTimeHours = FMath::Max(1, LeadTimeHours);

	// Confidence decays with lead time, improves with forecast technology.
	const float TechFactor = FMath::Clamp(ForecastTechnologyLevel, 0.2f, 2.0f);
	const float LeadTimeDecay = FMath::Clamp(1.0f - (Forecast.LeadTimeHours / (48.0f * TechFactor)), 0.1f, 0.95f);
	Forecast.Confidence = FMath::Clamp(LeadTimeDecay * TechFactor, 0.1f, 0.95f);

	// Naive persistence-plus-noise model: current conditions extrapolated
	// forward with noise scaled by (1-Confidence), which is enough for
	// gameplay-facing forecasts without a full atmospheric simulation.
	const float NoiseScale = 1.0f - Forecast.Confidence;
	Forecast.PredictedWaveHeightMeters = FMath::Max(0.1f,
		CurrentState.WaveHeightMeters + FMath::FRandRange(-2.0f, 2.0f) * NoiseScale);
	Forecast.PredictedVisibilityKm = FMath::Clamp(
		CurrentState.VisibilityKm + FMath::FRandRange(-10.0f, 10.0f) * NoiseScale, 0.2f, 40.0f);

	Forecast.PredictedWeather = CurrentState.Weather;
	if (CurrentState.ThreatLevel > 0.4f && FMath::FRand() < 0.3f * NoiseScale)
	{
		Forecast.PredictedWeather = EWeatherState::Storm;
	}

	return Forecast;
}
