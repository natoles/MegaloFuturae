// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCardHandWidget.h"
#include "MEGGamemode.h"
#include "Kismet/GameplayStatics.h"

void UMEGCardHandWidget::NativeConstruct()
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if(!ensure(GameMode != nullptr))
		return;

	GameMode->OnCardHandUpdatedDelegate.BindUObject(this, &UMEGCardHandWidget::UpdateHand);
}

void UMEGCardHandWidget::NativeDestruct()
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	GameMode->OnCardHandUpdatedDelegate.Unbind();
}

void UMEGCardHandWidget::UpdateHand()
{
	
}


