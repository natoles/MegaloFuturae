// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/MEGCellData.h"
#include "MEGCellWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEGALOFUTURAE_API UMEGCellWidget : public UUserWidget
{
	GENERATED_BODY()

public :

	void UpdateCell(EMEGDistrict InDistrictType, TArray<EMEGRoad> InRoads);

	EMEGDistrict DistrictType;

	TArray<EMEGRoad> Roads;

protected :

	void UpdateDistrict(EMEGDistrict InDistrictType);

	void UpdateRoads(TArray<EMEGRoad> InRoads);

	UFUNCTION(BlueprintImplementableEvent)
	void TestFunc(TArray<EMEGRoad>& InRoads);

	UPROPERTY(meta = (BindWidget))
	class UImage* DistrictImage;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* UpBox;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* RightBox;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* DownBox;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* LeftBox;

};
