// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MEGCardHandWidget.generated.h"

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

	UPROPERTY(meta = (BindWidget))
	class UMEGCardWidget* FirstCard;

	UPROPERTY(meta = (BindWidget))
	class UMEGCardWidget* SecondCard;

	UPROPERTY(meta = (BindWidget))
	class UMEGCardWidget* ThirdCard;
	
};
