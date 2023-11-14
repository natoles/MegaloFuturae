// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MEGCardHandWidget.generated.h"

class UMEGCardWidget;

/**
 * 
 */
UCLASS()
class MEGALOFUTURAE_API UMEGCardHandWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected :

	void UpdateHand();

	void DeselectAllCards();

	UMEGCardWidget* GetCardWidgetFomId(int32 CardId);

	UFUNCTION()
	void OnCardSelected(int32 InCardId);

	UFUNCTION()
	void OnRequestPlaceCard(FVector2D InCoords);

	int32 SelectedCardId = INDEX_NONE;

	void FillCardWidgets();
	TArray<UMEGCardWidget*> CardWidgets;

	UPROPERTY(meta = (BindWidget))
	UMEGCardWidget* FirstCard;

	UPROPERTY(meta = (BindWidget))
	UMEGCardWidget* SecondCard;

	UPROPERTY(meta = (BindWidget))
	UMEGCardWidget* ThirdCard;
	
};
