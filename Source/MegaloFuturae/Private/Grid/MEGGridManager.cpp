// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/MEGGridManager.h"
#include "Grid/MEGGridManager.h"
#include "Kismet/GameplayStatics.h"
#include "MEGGamemode.h"
#include "Data/MEGCardData.h"
#include "Grid/MEGGridManager.h"
#include "Grid/MEGGridCell.h"
#include "Grid/MEGCardPlacer.h"

#define CELL_LENGTH 70
#define CELL_HEIGHT 50
#define DEFAULT_CELL_Z 1

// Sets default values
AMEGGridManager::AMEGGridManager()
{

}

void AMEGGridManager::PlaceCard(int32 InCardId, FVector2D InCoords)
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	const FMEGCardData* CardData = GameMode->GetCardDataFromId(InCardId);
	if(!ensure(CardData != nullptr))
		return;

	for (const TPair<EMEGCellPosition, FMEGCellData>& CellData : CardData->Cells)
	{
		const FVector2D OffsetCoords = InCoords + GetCellPositionOffset(CellData.Key);

		AMEGGridCell* CurrentGridCell = GetCellFromCoords(OffsetCoords);
		if (CurrentGridCell == nullptr)
		{
			CurrentGridCell = GetWorld()->SpawnActor<AMEGGridCell>(GridCellClass);
			if(!ensure(CurrentGridCell != nullptr))
				continue;

			GridCells.Add(CurrentGridCell);

			const FVector SpawnPosition = FVector(OffsetCoords.X * CELL_LENGTH, OffsetCoords.Y * CELL_HEIGHT, DEFAULT_CELL_Z);
			CurrentGridCell->SetActorLocation(SpawnPosition);
			CurrentGridCell->Coords = OffsetCoords;
		}

		if(!ensure(CurrentGridCell != nullptr))
			continue;

		CurrentGridCell->UpdateCellDistrict(CellData.Value.DistrictType);
	}

	UpdateCardPlacers(InCoords);
}

void AMEGGridManager::UpdateCardPlacers(FVector2D InCoords)
{
	for (int32 XOffset = -2; XOffset <= 2; XOffset++)
	{
		for (int32 YOffset = -2; YOffset<= 2; YOffset++)
		{
			if(abs(XOffset) + abs(YOffset) == 4)
				continue;

			const int32 CurrentXCoord = InCoords.X + XOffset;
			const int32 CurrentYCoord = InCoords.Y + YOffset;

			AMEGCardPlacer* CurrentPlacer = GetCardPlacerFromCoords(FVector2D(CurrentXCoord, CurrentYCoord));
			if (CurrentPlacer == nullptr) // If placer not found, create it
			{
				CurrentPlacer = GetWorld()->SpawnActor<AMEGCardPlacer>(CardPlacerClass);
				if (!ensure(CurrentPlacer != nullptr))
					continue;

				CurrentPlacer->Coords = FVector2D(CurrentXCoord, CurrentYCoord);

				const FVector CurrentCoords = FVector(CurrentXCoord * CELL_LENGTH, CurrentYCoord * CELL_HEIGHT, DEFAULT_CELL_Z);
				CurrentPlacer->SetActorLocation(CurrentCoords);

				CardPlacers.Add(CurrentPlacer);
			}
		}
	}
}

AMEGCardPlacer* AMEGGridManager::GetCardPlacerFromCoords(FVector2D InCoords) const
{
	AMEGCardPlacer* const* Placer = CardPlacers.FindByPredicate([InCoords](const AMEGCardPlacer* InPlacer)
		{
			return InPlacer->Coords == InCoords;
		});

	if (Placer == nullptr)
		return nullptr;

	return *Placer;
}

AMEGGridCell* AMEGGridManager::GetCellFromCoords(FVector2D InCoords) const
{
	AMEGGridCell* const * GridCell = GridCells.FindByPredicate([InCoords](const AMEGGridCell* InGridCell)
		{
			return InGridCell->Coords == InCoords;
		});

	if(GridCell == nullptr)
		return nullptr;

	return *GridCell;
}

FVector2D AMEGGridManager::GetCellPositionOffset(EMEGCellPosition InCellPosition) const
{
	switch (InCellPosition)
	{
	case EMEGCellPosition::UL:
		return FVector2D(-1, -1);
		break;
	case EMEGCellPosition::UR:
		return FVector2D(0, -1);
		break;
	case EMEGCellPosition::DL:
		return FVector2D(-1, 0);
		break;
	case EMEGCellPosition::DR:
	default:
		return FVector2D(0, 0);
		break;
	}
}


