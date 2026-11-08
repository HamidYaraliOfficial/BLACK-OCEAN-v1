#pragma once

#include "CoreMinimal.h"
#include "BlackOceanTypes.h"
#include "DifficultySettings.generated.h"

// Difficulty in BLACK OCEAN deliberately does NOT just scale enemy health or
// damage. It scales the quality of information, environmental severity,
// resource scarcity and AI coordination, per the design pillar of
// imperfect information mattering more than raw stat inflation.
USTRUCT(BlueprintType)
struct FDifficultySettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Difficulty", meta=(ClampMin="0.0", ClampMax="1.0"))
	float SensorReliabilityMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Difficulty", meta=(ClampMin="0.0", ClampMax="2.0"))
	float WeatherSeverityMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Difficulty", meta=(ClampMin="0.0", ClampMax="2.0"))
	float ResourceScarcityMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Difficulty", meta=(ClampMin="0.0", ClampMax="1.0"))
	float AICoordinationLevel = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Difficulty", meta=(ClampMin="0.0", ClampMax="2.0"))
	float MissionComplexityMultiplier = 1.0f;

	static FDifficultySettings MakePreset(EDifficultyLevel Level)
	{
		FDifficultySettings S;
		switch (Level)
		{
			case EDifficultyLevel::Casual:
				S.SensorReliabilityMultiplier = 1.2f; S.WeatherSeverityMultiplier = 0.7f;
				S.ResourceScarcityMultiplier = 0.6f; S.AICoordinationLevel = 0.3f;
				S.MissionComplexityMultiplier = 0.7f;
				break;
			case EDifficultyLevel::Standard:
				// Defaults above already represent Standard.
				break;
			case EDifficultyLevel::Veteran:
				S.SensorReliabilityMultiplier = 0.8f; S.WeatherSeverityMultiplier = 1.2f;
				S.ResourceScarcityMultiplier = 1.3f; S.AICoordinationLevel = 0.7f;
				S.MissionComplexityMultiplier = 1.25f;
				break;
			case EDifficultyLevel::Extreme:
				S.SensorReliabilityMultiplier = 0.6f; S.WeatherSeverityMultiplier = 1.5f;
				S.ResourceScarcityMultiplier = 1.6f; S.AICoordinationLevel = 0.9f;
				S.MissionComplexityMultiplier = 1.5f;
				break;
			case EDifficultyLevel::Custom:
			default:
				break; // Caller fills in Custom values explicitly.
		}
		return S;
	}
};
