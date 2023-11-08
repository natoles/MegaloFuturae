// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MEGCardWidget.h"

#include "Data/MEGCardData.h"

void UMEGCardWidget::NativeConstruct()
{
	FillCellWidgets();
}

void UMEGCardWidget::UpdateCard(int32 CardId)
{
}

void UMEGCardWidget::FillCellWidgets()
{
	CellWidgets.Add({EMEGCellPosition::UL, CellUL});
	CellWidgets.Add({EMEGCellPosition::UR, CellUR});
	CellWidgets.Add({EMEGCellPosition::DR, CellDR});
	CellWidgets.Add({EMEGCellPosition::DL, CellDL});
}
