// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MEGScoringStrategy.generated.h"

class AMEGGridCell;

 UCLASS()
class MEGALOFUTURAE_API UMEGScoringStrategy : public UObject
{
	GENERATED_BODY()
public:

	virtual int32 GetScore(const TArray<AMEGGridCell*>& GridCells) const {return 0;}

	UPROPERTY(EditDefaultsOnly)
	int32 ScoringGoal = -1;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* ScoringImage;
};

UCLASS(Blueprintable)
class MEGALOFUTURAE_API UMEGScoreGoGreen : public UMEGScoringStrategy
{
	GENERATED_BODY()

public:

	virtual int32 GetScore(const TArray<AMEGGridCell*>& GridCells) const override;
};


UCLASS(Blueprintable)
class MEGALOFUTURAE_API UMEGScoreBloomBloom : public UMEGScoringStrategy
{
	GENERATED_BODY()

public:

	virtual int32 GetScore(const TArray<AMEGGridCell*>& GridCells) const override {return 0;}
};

UCLASS(Blueprintable)
class MEGALOFUTURAE_API UMEGScoreTheOutSkirts : public UMEGScoringStrategy
{
	GENERATED_BODY()

public:

	virtual int32 GetScore(const TArray<AMEGGridCell*>& GridCells) const override {return 0;}
};

