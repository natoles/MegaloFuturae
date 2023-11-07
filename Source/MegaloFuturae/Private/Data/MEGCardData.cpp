// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/MEGCardData.h"

FMEGCardData::FMEGCardData()
{
	for (EMEGCellPosition Position : TEnumRange<EMEGCellPosition>())
	{
		Cells.Add({ Position, FMEGCellData() });
	}
}

FMEGCardData::~FMEGCardData()
{
}
