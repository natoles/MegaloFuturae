// Fill out your copyright notice in the Description page of Project Settings.


#include "MEGPawn.h"

#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
AMEGPawn::AMEGPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	if (!ensure(CameraComponent != nullptr))
		return;

	CameraComponent->SetupAttachment(RootComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");
	if (!ensure(MovementComponent != nullptr))
		return;
}

// Called when the game starts or when spawned
void AMEGPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMEGPawn::MoveForward(float MovementDelta)
{
	AddMovementInput(GetActorForwardVector(), MovementDelta);
}

void AMEGPawn::MoveRight(float MovementDelta)
{
	AddMovementInput(GetActorRightVector(), MovementDelta);
}

// Called every frame
void AMEGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMEGPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMEGPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMEGPawn::MoveRight);
}

