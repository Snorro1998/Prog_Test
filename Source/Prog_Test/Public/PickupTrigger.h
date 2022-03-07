// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/TriggerBox.h"
#include "PickupTrigger.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class PROG_TEST_API APickupTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay();

public:

	//UPROPERTY(EditAnywhere)
	//	UStaticMeshComponent* meshComponent;

	//UPROPERTY(EditAnywhere)
	//	UStaticMesh* mesh;

	APickupTrigger();
	UFUNCTION()
		void Event(class AActor* overlappedActor, class AActor* otherActor);

	//UPROPERTY(EditAnywhere)
	//	USceneComponent* sceneObject;

	UPROPERTY(EditAnywhere)
		AActor* owningActor;

	UPROPERTY(EditAnywhere)
		AActor* affectedActor;
};
