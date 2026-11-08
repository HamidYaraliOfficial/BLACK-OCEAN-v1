#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlackOceanTypes.h"
#include "BlackOceanWidgetBase.generated.h"

// Base class every BLACK OCEAN UMG widget should derive from (in Blueprint,
// set this as the parent class). On construction and whenever the player
// changes theme/language in Settings, it re-applies the active palette and
// flow direction automatically, and exposes BlueprintImplementableEvents so
// widget Blueprints can react (recolor borders, flip layout, etc.) without
// each widget re-querying the subsystems itself.
UCLASS(Abstract)
class UBlackOceanWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	// Call after UUIThemeSubsystem::SetTheme or ULocalizationSubsystem::SetLanguage
	// so already-open widgets refresh without needing to be recreated.
	UFUNCTION(BlueprintCallable, Category="BlackOcean|UI")
	void RefreshThemeAndLocalization();

protected:
	// Implemented in the widget Blueprint: apply NewTheme's palette to this
	// widget's brushes/colors.
	UFUNCTION(BlueprintImplementableEvent, Category="BlackOcean|UI")
	void OnThemeChanged(EUITheme NewTheme);

	// Implemented in the widget Blueprint: call SetFlowDirectionPreference /
	// mirror layout as needed for NewDirection.
	UFUNCTION(BlueprintImplementableEvent, Category="BlackOcean|UI")
	void OnFlowDirectionChanged(ETextFlowDirection NewDirection);
};
