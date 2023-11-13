// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/MEGGridManager.h"
#include "Grid/MEGGridManager.h"
#include "Kismet/GameplayStatics.h"
#include "MEGGamemode.h"
#include "Data/MEGCardData.h"

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
	}
}

// Called when the game starts or when spawned
void AMEGGridManager::BeginPlay()
{
	Super::BeginPlay();
	
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


