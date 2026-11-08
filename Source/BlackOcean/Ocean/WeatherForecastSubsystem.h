#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OceanRegionData.h"
#include "WeatherForecastSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FWeatherForecast
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Weather")
	FName RegionId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Weather")
	EWeatherState PredictedWeather = EWeatherState::Clear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Weather")
	float PredictedWaveHeightMeters = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Weather")
	float PredictedVisibilityKm = 20.0f;

	// How many campaign hours ahead this forecast looks.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Weather")
	int32 LeadTimeHours = 12;

	// 0-1: how much to trust this forecast; lower with longer lead time and
	// worse sensor/weather-satellite technology. Never a guarantee.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Weather", meta=(ClampMin="0.0", ClampMax="1.0"))
	float Confidence = 0.7f;
};

// Produces probabilistic, technology-gated weather forecasts from current
// ocean-region state. Forecasts are never certain — Confidence should be
// surfaced in the UI (e.g. "60% confidence") rather than treated as fact.
UCLASS()
class UWeatherForecastSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|Weather")
	FWeatherForecast GenerateForecast(const FOceanRegionState& CurrentState, int32 LeadTimeHours, float ForecastTechnologyLevel) const;
};
