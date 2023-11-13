// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/MEGCardData.h"
#include "MEGGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MEGALOFUTURAE_API AMEGGamemode : public AGameModeBase
{
	GENERATED_BODY()

public : 

	virtual void BeginPlay() override;

	const FMEGCardData* GetCardDataFromId(int32 InCardId) const;

	const struct FMEGDistrictDataRow* GetDistrictData(EMEGDistrict DistrictType) const;

	/******  Card containers  ******/

	TArray<int32> DrawnCardsId;
	TArray<int32> PlayedCardsId;
	TArray<int32> ScoringCardsId;

	UPROPERTY(EditDefaultsOnly)
	TArray<FMEGCardData> Cards;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	DECLARE_DELEGATE(FOnCardHandUpdated)
	FOnCardHandUpdated OnCardHandUpdatedDelegate;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCardSelected, int32 CardId)
	FOnCardSelected OnCardSelectedDelegate;

protected :

	void DrawCard();

	UPROPERTY(EditDefaultsOnly)
	class UDataTable* DistrictDataTable;

	/* Returns a card id from a card which is available. Returns INDEX_NONE if no card left */
	int32 GetAvailableCardId() const;
};
