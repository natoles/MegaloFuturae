// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/MEGCardPlacer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Grid/MEGCardPlacer.h"
#include "Kismet/GameplayStatics.h"
#include "MEGGamemode.h"


// Sets default values
AMEGCardPlacer::AMEGCardPlacer()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	MeshComponent->SetupAttachment(SceneComponent);
}

void AMEGCardPlacer::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->OnClicked.AddDynamic(this, &AMEGCardPlacer::OnMeshClicked);
}

void AMEGCardPlacer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	MeshComponent->OnClicked.RemoveAll(this);
}

void AMEGCardPlacer::OnMeshClicked(UPrimitiveComponent* Component, FKey ButtonPressed)
{
	AMEGGamemode* GameMode = Cast<AMEGGamemode>(UGameplayStatics::GetGameMode(this));
	if (!ensure(GameMode != nullptr))
		return;

	GameMode->OnRequestPlaceCard.Broadcast(Coords);
}


