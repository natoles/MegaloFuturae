// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/MEGGridCell.h"
#include "UI/MEGCellWidget.h"

#include "Components/WidgetComponent.h"

// Sets default values
AMEGGridCell::AMEGGridCell()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	CellWidget = CreateDefaultSubobject<UWidgetComponent>("CellWidget");
	CellWidget->SetupAttachment(RootComponent);
}

void AMEGGridCell::UpdateCellWidget(EMEGDistrict DistrictType, TArray<EMEGRoad> Roads)
{
	if (UMEGCellWidget* CastCellWidget = Cast<UMEGCellWidget>(CellWidget->GetUserWidgetObject()))
	{
		CastCellWidget->UpdateCell(DistrictType, Roads);
	}
}

EMEGDistrict AMEGGridCell::GetDistrictType() const
{
	if (const UMEGCellWidget* CastCellWidget = Cast<UMEGCellWidget>(CellWidget->GetUserWidgetObject()))
	{
		return CastCellWidget->DistrictType;
	}

	check(false);
	return EMEGDistrict::Parc;
}

const TArray<EMEGRoad> AMEGGridCell::GetRoads() const
{
	if (const UMEGCellWidget* CastCellWidget = Cast<UMEGCellWidget>(CellWidget->GetUserWidgetObject()))
	{
		return CastCellWidget->Roads;
	}

	check(false);
	return TArray<EMEGRoad>();
}


