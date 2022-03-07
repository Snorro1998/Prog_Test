// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupTrigger.h"

APickupTrigger::APickupTrigger() {
	OnActorBeginOverlap.AddDynamic(this, &APickupTrigger::Event);
	owningActor = GetOwner();

	if (owningActor != nullptr)
	{
		owningActor->CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	}

	/*
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("<name>"));
	meshComponent->SetStaticMesh(mesh);
	USceneComponent* sceneThing = GetOwner()->GetRootComponent();*/
	/*meshComponent->AttachToComponent(/*RootComponentsceneThing, FAttachmentTransformRules::KeepRelativeTransform);*/
}

void APickupTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void APickupTrigger::Event(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor != nullptr && otherActor != this)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("OnActorOverlap"));
		/*
		if (affectedActor)
		{
			affectedActor->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
		}
		*/
	}
}