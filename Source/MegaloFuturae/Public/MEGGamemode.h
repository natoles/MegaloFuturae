// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Data/MEGCardData.h"
#include "MEGGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MEGALOFUTURAE_API AMEGGamemode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TArray<FMEGCardData> Cards;
};
