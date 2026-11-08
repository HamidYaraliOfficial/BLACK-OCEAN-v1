#include "PhotoModeComponent.h"

UPhotoModeComponent::UPhotoModeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPhotoModeComponent::Enter()
{
	bIsActive = true;
}

void UPhotoModeComponent::Exit()
{
	bIsActive = false;
}
