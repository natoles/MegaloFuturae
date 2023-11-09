// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCellWidget.h"

#include "MEGGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MEGDistrictDataRow.h"
#include "Components/Image.h"

void UMEGCellWidget::UpdateCell(EMEGDistrict InDistrictType)
{
	DistrictType = InDistrictType;

	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	const FMEGDistrictDataRow* DistrictDataRow = GameMode->GetDistrictData(DistrictType);
	if(!ensure(DistrictDataRow != nullptr))
		return;

	DistrictImage->SetBrushFromTexture(DistrictDataRow->DistrictImage);
}
