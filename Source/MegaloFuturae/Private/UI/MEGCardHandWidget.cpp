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
	GameMode->OnCardSelectedDelegate.AddUObject(this, &UMEGCardHandWidget::OnCardSelected);
	GameMode->OnRequestPlaceCard.AddUObject(this, &UMEGCardHandWidget::OnRequestPlaceCard);
}

void UMEGCardHandWidget::NativeDestruct()
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	GameMode->OnCardHandUpdatedDelegate.Unbind();
	GameMode->OnCardSelectedDelegate.RemoveAll(this);
	GameMode->OnRequestPlaceCard.RemoveAll(this);
}

void UMEGCardHandWidget::UpdateHand()
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	const int32 NumCardsInHand = GameMode->DrawnCardsId.Num();
	for (int32 Index = 0; Index < CardWidgets.Num(); Index++)
	{
		if(!ensure(CardWidgets[Index] != nullptr))
			continue;

		if (Index >= NumCardsInHand)
		{
			CardWidgets[Index]->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}

		CardWidgets[Index]->SetVisibility(ESlateVisibility::Visible);
		CardWidgets[Index]->UpdateCard(GameMode->DrawnCardsId[Index]);
	}

}

void UMEGCardHandWidget::DeselectAllCards()
{
	for (UMEGCardWidget* CardWidget : CardWidgets)
	{
		CardWidget->SetSelected(false);
	}

	SelectedCardId = INDEX_NONE;
}

UMEGCardWidget* UMEGCardHandWidget::GetCardWidgetFomId(int32 CardId)
{
	for (UMEGCardWidget* CardWidget : CardWidgets)
	{
		if(CardWidget->CardId == CardId)
			return CardWidget;
	}

	return nullptr;
}

void UMEGCardHandWidget::OnCardSelected(int32 InCardId)
{
	// If we select a card already selected, deselect it
	const bool bSelectCard = (SelectedCardId != InCardId);

	DeselectAllCards();
	if (bSelectCard)
	{
		SelectedCardId = InCardId;
		UMEGCardWidget* SelectedCard = GetCardWidgetFomId(SelectedCardId);
		if(!ensure(SelectedCard != nullptr))
			return;

		SelectedCard->SetSelected(true);
	}
}

void UMEGCardHandWidget::OnRequestPlaceCard(FVector2D InCoords)
{
	// Don't do anything if no card is selected
	if(SelectedCardId == INDEX_NONE)
		return;

	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	GameMode->PlaceCardFromHand(SelectedCardId, InCoords);
	DeselectAllCards();
}

void UMEGCardHandWidget::FillCardWidgets()
{
	CardWidgets.Add(FirstCard);
	CardWidgets.Add(SecondCard);
	CardWidgets.Add(ThirdCard);
}


