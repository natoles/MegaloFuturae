// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MEGCellData.h"
#include "MEGCardData.generated.h"

UENUM()
enum class EMEGCellPosition
{
	UL,
	UR,
	DR,
	DL
};

ENUM_RANGE_BY_FIRST_AND_LAST(EMEGCellPosition, EMEGCellPosition::UL, EMEGCellPosition::DL)

/**
 * 
 */
USTRUCT()
struct MEGALOFUTURAE_API FMEGCardData
{
	GENERATED_BODY()

public:
	FMEGCardData();
	~FMEGCardData();

	UPROPERTY(EditDefaultsOnly)
	TMap<EMEGCellPosition, FMEGCellData> Cells;
};
