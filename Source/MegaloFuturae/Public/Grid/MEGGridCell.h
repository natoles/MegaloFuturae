// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/MEGCellData.h"
#include "MEGGridCell.generated.h"


UCLASS()
class MEGALOFUTURAE_API AMEGGridCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMEGGridCell();

	FVector2D Coords;

	void UpdateCellWidget(EMEGDistrict DistrictType, TArray<EMEGRoad> Roads);

	EMEGDistrict GetDistrictType() const;

	const TArray<EMEGRoad> GetRoads() const;

protected:

	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* CellWidget;

};
