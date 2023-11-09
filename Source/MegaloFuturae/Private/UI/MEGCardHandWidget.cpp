// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCardHandWidget.h"
#include "MEGGamemode.h"
#include "UI/MEGCardWidget.h"
#include "Kismet/GameplayStatics.h"

void UMEGCardHandWidget::NativeConstruct()
{
	FillCardWidgets();

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
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	const int32 NumCardsInHand = GameMode->DrawnCardsId.Num();
	for (int32 Index = 0; Index < CardWidgets.Num(); Index++)
	{
		if (Index >= NumCardsInHand)
		{
			CardWidgets[Index]->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		CardWidgets[Index]->SetVisibility(ESlateVisibility::Visible);
		CardWidgets[Index]->UpdateCard(GameMode->DrawnCardsId[Index]);
	}

}

void UMEGCardHandWidget::FillCardWidgets()
{
	CardWidgets.Add(FirstCard);
	CardWidgets.Add(SecondCard);
	CardWidgets.Add(ThirdCard);
}


