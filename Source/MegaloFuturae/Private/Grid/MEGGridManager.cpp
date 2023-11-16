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

		CurrentGridCell->UpdateCellWidget(CellData.Value.DistrictType, CellData.Value.Roads);
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

int32 AMEGGridManager::GetBiggestDistrictClusterSize(const EMEGDistrict InDistrictType) const
{
	TArray<FVector2D> VisitedCoords;
	int32 BiggestClusterSize = 0;

	for (const AMEGGridCell* GridCell : GridCells)
	{
		if (!ensure(GridCell != nullptr))
			continue;

		if (GridCell->GetDistrictType() != InDistrictType)
			continue;

		// Skip it if already visited
		if (VisitedCoords.Contains(GridCell->Coords))
			continue;

		const int32 ClusterSize = GetDistrictClusterSize(GridCell, GridCell->GetDistrictType(), VisitedCoords);
		BiggestClusterSize = ClusterSize > BiggestClusterSize ? ClusterSize : BiggestClusterSize;
	}

	return BiggestClusterSize;
}

int32 AMEGGridManager::GetDistrictClusterSize(const AMEGGridCell* InGridCell, const EMEGDistrict District, TArray<FVector2D>& VisitedCoords) const
{
	if (InGridCell->GetDistrictType() != District)
		return 0;

	// If cell already visited, return
	if (VisitedCoords.Contains(InGridCell->Coords))
		return 0;

	VisitedCoords.Add(InGridCell->Coords);

	int32 Size = 1;

	// Call the function recursively on all 4 neighbors (if they exist)
	for (const FVector2D NeighBorCoords : NeighborsOffset)
	{
		const FVector2D NeighBorCellGridCoords = InGridCell->Coords + NeighBorCoords;

		const AMEGGridCell* NeighBorCell = GetCellFromCoords(InGridCell->Coords + NeighBorCoords);
		if (NeighBorCell == nullptr) // There are no cell at this coord
			continue;

		Size += GetDistrictClusterSize(NeighBorCell, District, VisitedCoords);
	}

	return Size;
}

int32 AMEGGridManager::GetRoadCount() const
{
	TArray<FVector2D> VisitedCoords;
	int32 NumRoads = 0;

	for (const AMEGGridCell* GridCell : GridCells)
	{
		if (!ensure(GridCell != nullptr))
			continue;

		if (GridCell->GetRoads().Num() == 0)
			continue; // No roads

		// Skip it if already visited
		if (VisitedCoords.Contains(GridCell->Coords))
			continue;

		NumRoads++;

		// No need to know the length of the road, we just want to mark this entire road as visited
		VisitSingleRoad(GridCell, VisitedCoords);
	}

	return NumRoads;
}

void AMEGGridManager::VisitSingleRoad(const AMEGGridCell* InGridCell, TArray<FVector2D>& VisitedCoords) const
{
	if (InGridCell->GetRoads().Num() == 0)
		return; // No roads

	if (VisitedCoords.Contains(InGridCell->Coords))
		return;

	VisitedCoords.Add(InGridCell->Coords);

	// Check every road direction to see if it's connected on a neighbor cell
	for (const EMEGRoad Road : InGridCell->GetRoads())
	{
		const FVector2D Offset = GetRoadNeighborOffset(Road);
		const AMEGGridCell* NeighBorCell = GetCellFromCoords(InGridCell->Coords + Offset);
		if (NeighBorCell == nullptr) // There are no cell at this coord
			continue;

		if (!NeighBorCell->GetRoads().Contains(GetOppositeRoad(Road)))
			continue;

		VisitSingleRoad(NeighBorCell, VisitedCoords);
	}
}

const FVector2D AMEGGridManager::GetRoadNeighborOffset(const EMEGRoad& Road) const
{
	switch (Road)
	{
	case EMEGRoad::Up:
		return FVector2D(0, -1);
	case EMEGRoad::Down:
		return FVector2D(0, 1);
	case EMEGRoad::Left:
		return FVector2D(-1, 0);
	case EMEGRoad::Right:
		return FVector2D(0, 1);
	default:
		return FVector2D(0, 0);
	}
}

const EMEGRoad AMEGGridManager::GetOppositeRoad(const EMEGRoad InitialDirection) const
{
	int32 IntDirection = (int32)InitialDirection;
	IntDirection = (IntDirection + 2) % 4;
	const EMEGRoad OppositeDirection = (EMEGRoad)IntDirection;
	return OppositeDirection;
}




