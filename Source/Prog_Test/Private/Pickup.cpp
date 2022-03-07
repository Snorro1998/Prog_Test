// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Sound/SoundCue.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator newRot = FRotator(rotSpeed.X, rotSpeed.Y, rotSpeed.Z);
	FQuat QuatRotation = FQuat(newRot);
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}
