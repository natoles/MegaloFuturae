// Fill out your copyright notice in the Description page of Project Settings.


#include "Score/MEGScoringStrategy.h"
#include "Grid/MEGGridCell.h"
#include "Data/MEGCellData.h"

int32 UMEGScoreGoGreen::GetScore(const TArray<AMEGGridCell*>& GridCells) const
{
	int32 Score = 0;
	for (const AMEGGridCell* GridCell : GridCells)
	{
		switch (GridCell->GetDistrictType())
		{
			case EMEGDistrict::Industry :
				Score -= 3;
				break;
			case EMEGDistrict::Parc :
				Score += 1;
				break;
			default :
				break;
		}
	}

	return Score;
}
