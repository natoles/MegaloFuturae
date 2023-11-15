// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MEGGridCell.generated.h"

enum class EMEGDistrict;

UCLASS()
class MEGALOFUTURAE_API AMEGGridCell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMEGGridCell();

	FVector2D Coords;

	void UpdateCellDistrict(EMEGDistrict DistrictType);

	EMEGDistrict GetDistrictType() const;

protected:

	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* CellWidget;

};
