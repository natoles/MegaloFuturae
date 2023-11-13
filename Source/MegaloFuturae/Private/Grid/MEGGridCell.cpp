// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/MEGGridCell.h"

#include "Components/WidgetComponent.h"

// Sets default values
AMEGGridCell::AMEGGridCell()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	CellWidget = CreateDefaultSubobject<UWidgetComponent>("CellWidget");
	CellWidget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMEGGridCell::BeginPlay()
{
	Super::BeginPlay();
	
}

