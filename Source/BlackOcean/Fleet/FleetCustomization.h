#pragma once

#include "CoreMinimal.h"
#include "FleetCustomization.generated.h"

// Purely cosmetic, fully fictional customization for a fleet or vessel:
// colors, emblem, name and an in-universe classification label the player
// invents. None of this affects simulation balance.
USTRUCT(BlueprintType)
struct FFleetCustomization
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Customization")
	FLinearColor PrimaryColor = FLinearColor(0.1f, 0.3f, 0.5f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Customization")
	FLinearColor SecondaryColor = FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Customization")
	FName EmblemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Customization")
	FText CustomFleetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Customization")
	FText CustomClassificationLabel;
};
