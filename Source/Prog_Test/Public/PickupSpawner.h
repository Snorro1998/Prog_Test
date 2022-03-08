// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <iostream>
#include <list>
#include <limits>
#include "Pickup.h"
#include "CoreMinimal.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Actor.h"
#include "PickupSpawner.generated.h"

USTRUCT()
struct FSoundSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float minPitch;

	UPROPERTY(EditAnywhere)
		float maxPitch;

	UPROPERTY(EditAnywhere)
		float minVolume;

	UPROPERTY(EditAnywhere)
		float maxVolume;

	FSoundSettings()
	{
		minPitch = 0.5f;
		maxPitch = 2.0f;
		minVolume = 0.5f;
		maxVolume = 2.0f;
	}
};

UCLASS()
class PROG_TEST_API APickupSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		int itoaValue;

	UPROPERTY(EditAnywhere)
		int itoaBase;

	UPROPERTY(EditAnywhere)
		FString itoaString;

	UFUNCTION(BlueprintCallable)
		int GetNPicks();

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<AActor>> spawnablePickups;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> spawnObjPickup;

	UPROPERTY(EditAnywhere)
		float spawnInterval;

	UPROPERTY(EditAnywhere)
		int maxPickups;

	UPROPERTY(BlueprintReadWrite)
		int nCollectedPickups;

	std::list<APickup*> listPickups;
	FTimerHandle MyTimerHandle;

	UWorld* world;
	AActor* playerActor;
	FVector playerPosition;

	std::string itoa(int value, int base);
	void SpawnPickup();
	APickup* GetClosetsPickup();
	void CheckPickups();
	void PlaySoundAtActor(USoundCue* sound, AActor* actor);

private:
	UPROPERTY(EditAnywhere, Category = "Sound")
		FSoundSettings soundSettings;
};