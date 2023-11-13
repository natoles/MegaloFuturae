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

	GridManager = GetWorld()->SpawnActor<AMEGGridManager>(AMEGGridManager::StaticClass());
	if (!ensure(GridManager != nullptr))
		return;

	const int32 FirstPlacedCardId = GetAvailableCardId();
	GridManager->PlaceCard(FirstPlacedCardId, FVector2D(0,0));
	PlayedCardsId.Add(FirstPlacedCardId);
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
