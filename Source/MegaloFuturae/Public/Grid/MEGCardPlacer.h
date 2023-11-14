// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MEGCardPlacer.generated.h"

UCLASS()
class MEGALOFUTURAE_API AMEGCardPlacer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMEGCardPlacer();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnMeshClicked(UPrimitiveComponent* Component, FKey ButtonPressed);

	FVector2D Coords;

protected :

	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;
};
