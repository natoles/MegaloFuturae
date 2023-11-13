// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCardWidget.h"
#include "UI/MEGCellWidget.h"
#include "Data/MEGCardData.h"
#include "MEGGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UMEGCardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FillCellWidgets();

	SelectionButton->OnClicked.AddDynamic(this, &UMEGCardWidget::OnButtonClicked);
}

void UMEGCardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	SelectionButton->OnClicked.RemoveAll(this);
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

void UMEGCardWidget::OnButtonClicked()
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	GameMode->OnCardSelectedDelegate.Broadcast(CardId);
}

void UMEGCardWidget::SetSelected(bool bSelected)
{
	if (bSelected)
	{
		SelectedImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		SelectedImage->SetVisibility(ESlateVisibility::Collapsed);
	}
}
