#include "BlackOceanWidgetBase.h"
#include "UIThemeSubsystem.h"
#include "LocalizationSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UBlackOceanWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	RefreshThemeAndLocalization();
}

void UBlackOceanWidgetBase::RefreshThemeAndLocalization()
{
	if (const UGameInstance* GI = GetGameInstance())
	{
		if (UUIThemeSubsystem* ThemeSubsystem = GI->GetSubsystem<UUIThemeSubsystem>())
		{
			OnThemeChanged(ThemeSubsystem->GetCurrentTheme());
		}
		if (ULocalizationSubsystem* LocalizationSubsystem = GI->GetSubsystem<ULocalizationSubsystem>())
		{
			OnFlowDirectionChanged(LocalizationSubsystem->GetCurrentFlowDirection());
		}
	}
}
