#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhotoModeComponent.generated.h"

// Freezes simulation-visible camera controls (not the simulation clock
// itself) and exposes a small set of cosmetic capture parameters, for the
// Photo Mode / Cinematic Camera System.
UCLASS(ClassGroup=(BlackOcean), meta=(BlueprintSpawnableComponent))
class UPhotoModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPhotoModeComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|PhotoMode")
	float FieldOfView = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|PhotoMode")
	bool bHideHUD = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="BlackOcean|PhotoMode")
	FName ColorGradePresetId;

	UFUNCTION(BlueprintCallable, Category="BlackOcean|PhotoMode")
	void Enter();

	UFUNCTION(BlueprintCallable, Category="BlackOcean|PhotoMode")
	void Exit();

	UFUNCTION(BlueprintPure, Category="BlackOcean|PhotoMode")
	bool IsActive() const { return bIsActive; }

private:
	bool bIsActive = false;
};
