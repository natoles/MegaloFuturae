// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCellWidget.h"

#include "MEGGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MEGDistrictDataRow.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

void UMEGCellWidget::UpdateCell(EMEGDistrict InDistrictType, TArray<EMEGRoad> InRoads)
{
	UpdateDistrict(InDistrictType);
	UpdateRoads(InRoads);
}

void UMEGCellWidget::UpdateDistrict(EMEGDistrict InDistrictType)
{
	DistrictType = InDistrictType;

	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	const FMEGDistrictDataRow* DistrictDataRow = GameMode->GetDistrictData(DistrictType);
	if (!ensure(DistrictDataRow != nullptr))
		return;

	DistrictImage->SetBrushFromTexture(DistrictDataRow->DistrictImage);
}

void UMEGCellWidget::UpdateRoads(TArray<EMEGRoad> InRoads)
{
	Roads = InRoads;

	if(Roads.Contains(EMEGRoad::Up))
		UpBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	else 
		UpBox->SetVisibility(ESlateVisibility::Collapsed);

	if (Roads.Contains(EMEGRoad::Right))
		RightBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	else
		RightBox->SetVisibility(ESlateVisibility::Collapsed);

	if (Roads.Contains(EMEGRoad::Down))
		DownBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	else
		DownBox->SetVisibility(ESlateVisibility::Collapsed);

	if (Roads.Contains(EMEGRoad::Left))
		LeftBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	else
		LeftBox->SetVisibility(ESlateVisibility::Collapsed);
}