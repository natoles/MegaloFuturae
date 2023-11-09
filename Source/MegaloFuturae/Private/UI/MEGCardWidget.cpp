// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCardWidget.h"
#include "UI/MEGCellWidget.h"
#include "Data/MEGCardData.h"
#include "MEGGamemode.h"
#include "Kismet/GameplayStatics.h"

void UMEGCardWidget::NativeConstruct()
{
	FillCellWidgets();
}

void UMEGCardWidget::UpdateCard(int32 InCardId)
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	const FMEGCardData* CardData = GameMode->GetCardDataFromId(InCardId);
	if(!ensure(CardData != nullptr))
		return;

	CardId = InCardId;
	
	for (TPair<EMEGCellPosition, UMEGCellWidget*>& KvpCell : CellWidgets)
	{
		if(!ensure(KvpCell.Value != nullptr))
			return;

		const EMEGDistrict CellDistrict = CardData->Cells[KvpCell.Key].DistrictType;

		KvpCell.Value->UpdateCell(CellDistrict);
	}
}

void UMEGCardWidget::FillCellWidgets()
{
	CellWidgets.Add({EMEGCellPosition::UL, CellUL});
	CellWidgets.Add({EMEGCellPosition::UR, CellUR});
	CellWidgets.Add({EMEGCellPosition::DR, CellDR});
	CellWidgets.Add({EMEGCellPosition::DL, CellDL});
}
