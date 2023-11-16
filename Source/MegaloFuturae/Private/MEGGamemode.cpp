// Fill out your copyright notice in the Description page of Project Settings.


#include "MEGGamemode.h"
#include "Blueprint/UserWidget.h"
#include "Data/MEGDistrictDataRow.h"
#include "Grid/MEGGridManager.h"

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

	GridManager = GetWorld()->SpawnActor<AMEGGridManager>(GridManagerClass);
	if (!ensure(GridManager != nullptr))
		return;

	const int32 FirstPlacedCardId = GetAvailableCardId();
	GridManager->PlaceCard(FirstPlacedCardId, FVector2D(0,0));
	PlayedCardsId.Add(FirstPlacedCardId);
	UpdateScore();
}

void AMEGGamemode::DrawCard()
{
	const int32 DrawnCardId = GetAvailableCardId();
	if(DrawnCardId != INDEX_NONE)
		DrawnCardsId.Add(DrawnCardId);

	OnCardHandUpdatedDelegate.ExecuteIfBound();
}

const FMEGCardData* AMEGGamemode::GetCardDataFromId(int32 InCardId) const
{
	const FMEGCardData* CardData = Cards.FindByPredicate([InCardId](const FMEGCardData& InCardData)
		{
			return InCardData.CardId == InCardId;
		}) ;

	return CardData;
}

const FMEGDistrictDataRow* AMEGGamemode::GetDistrictData(EMEGDistrict DistrictType) const
{
	if(!ensure(DistrictDataTable != nullptr))
		return nullptr;

	TArray<FName> RowNames = DistrictDataTable->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FMEGDistrictDataRow* DistrictDataRow = DistrictDataTable->FindRow<FMEGDistrictDataRow>(RowName, "");

		if (DistrictDataRow && DistrictDataRow->DistrictType == DistrictType)
		{
			return DistrictDataRow;
		}
	}

	return nullptr;
}

void AMEGGamemode::PlaceCardFromHand(int32 InCardId, FVector2D InCoords)
{
	if(InCardId == INDEX_NONE)
		return;

	GridManager->PlaceCard(InCardId, InCoords);
	PlayedCardsId.Add(InCardId);
	RemoveCardFromHand(InCardId);

	UpdateScore();
	DrawCard();
}

void AMEGGamemode::RemoveCardFromHand(int32 CardId)
{
	DrawnCardsId.Remove(CardId);
	OnCardHandUpdatedDelegate.ExecuteIfBound();
}

void AMEGGamemode::UpdateScore()
{
	Score = 0;
	for (EMEGDistrict District : TEnumRange<EMEGDistrict>())
	{
		Score += GridManager->GetBiggestDistrictClusterSize(District);
	}

	Score -= GridManager->GetRoadCount();
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