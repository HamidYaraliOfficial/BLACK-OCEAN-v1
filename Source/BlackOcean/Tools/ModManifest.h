#pragma once

#include "CoreMinimal.h"
#include "ModManifest.generated.h"

// Declared by a mod package so the Modding System can validate compatibility
// before loading it, per the design spec's Version/Dependency Validation.
USTRUCT(BlueprintType)
struct FModManifest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Modding")
	FName ModId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Modding")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Modding")
	int32 RequiredGameContentVersion = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|Modding")
	TArray<FName> DependsOnModIds;

	static bool IsCompatible(const FModManifest& Mod, int32 CurrentGameContentVersion)
	{
		return Mod.RequiredGameContentVersion <= CurrentGameContentVersion;
	}
};
