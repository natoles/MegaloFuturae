// Fill out your copyright notice in the Description page of Project Settings.


#include "MEGGamemode.h"
#include "Blueprint/UserWidget.h"

#define MAX_CARDS_IN_HANDS 3

void AMEGGamemode::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	if(!ensure(HUDWidget != nullptr))
		return;

	HUDWidget->AddToViewport();

	for (int32 Index = 0; Index < MAX_CARDS_IN_HANDS; Index++)
	{
		DrawCard();
	}
}

void AMEGGamemode::DrawCard()
{
	const int32 DrawnCardId = GetAvailableCardId();
	if(DrawnCardId != INDEX_NONE)
		DrawnCardsId.Add(DrawnCardId);

	OnCardHandUpdatedDelegate.ExecuteIfBound();
}

int32 AMEGGamemode::GetAvailableCardId() const
{
	const TArray<FMEGCardData> AvailableCards = Cards.FilterByPredicate([this](const FMEGCardData& InCardData)
		{
			return !(DrawnCardsId.Contains(InCardData.CardId) 
						|| PlayedCardsId.Contains(InCardData.CardId)
						|| ScoringCardsId.Contains(InCardData.CardId));
		});

	if(AvailableCards.Num() == 0)
		return INDEX_NONE;

	const int32 CardIndex = rand() % AvailableCards.Num();
	return AvailableCards[CardIndex].CardId;
}
