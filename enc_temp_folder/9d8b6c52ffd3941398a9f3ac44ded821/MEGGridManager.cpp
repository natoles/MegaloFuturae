// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/MEGGridManager.h"
#include "Grid/MEGGridManager.h"
#include "Kismet/GameplayStatics.h"
#include "MEGGamemode.h"
#include "Data/MEGCardData.h"
#include "Grid/MEGGridManager.h"
#include "Grid/MEGGridCell.h"

#define CELL_LENGTH 70
#define CELL_HEIGHT 50
#define DEFAULT_CELL_Z 5

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
			// Spawn it !

			AMEGGridCell* NewGridCell = GetWorld()->SpawnActor<AMEGGridCell>(GridCellClass);
			if(!ensure(NewGridCell != nullptr))
				continue;

			GridCells.Add(NewGridCell);

			const FVector SpawnPosition = FVector(OffsetCoords.X * CELL_LENGTH, OffsetCoords.Y * CELL_HEIGHT, DEFAULT_CELL_Z);
			NewGridCell->SetActorLocation(SpawnPosition);
			NewGridCell->Coords = OffsetCoords;
		}

		// Update it !
	}
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


