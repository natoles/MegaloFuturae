// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MEGGridManager.generated.h"

UCLASS()
class MEGALOFUTURAE_API AMEGGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMEGGridManager();

	void PlaceCard(int32 InCardId, FVector2D InCoords);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector2D GetCellPositionOffset(enum class EMEGCellPosition InCellPosition) const;

	TArray<class AMEGGridCell*> GridCells;

};
