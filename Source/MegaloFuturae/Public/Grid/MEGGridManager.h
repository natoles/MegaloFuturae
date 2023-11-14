// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MEGGridManager.generated.h"

class AMEGGridCell;
class AMEGCardPlacer;
enum class EMEGCellPosition;

UCLASS()
class MEGALOFUTURAE_API AMEGGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMEGGridManager();

	void PlaceCard(int32 InCardId, FVector2D InCoords);


protected:

	FVector2D GetCellPositionOffset(EMEGCellPosition InCellPosition) const;
	AMEGGridCell* GetCellFromCoords(FVector2D InCoords) const;

	void UpdateCardPlacers(FVector2D InCoords);

	TArray<AMEGGridCell*> GridCells;

	TArray<AMEGCardPlacer*> CardPlacers;

	AMEGCardPlacer* GetCardPlacerFromCoords(FVector2D InCoords) const;

	// Specify the BP version from GridCell in the Editor
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMEGCardPlacer> CardPlacerClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AMEGGridCell> GridCellClass;

};
