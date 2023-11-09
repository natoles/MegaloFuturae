// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MEGCellData.h"
#include "Engine/DataTable.h"

#include "MEGDistrictDataRow.generated.h"

/**
 * 
 */
USTRUCT()
struct MEGALOFUTURAE_API FMEGDistrictDataRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	EMEGDistrict DistrictType;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* DistrictImage;
};
