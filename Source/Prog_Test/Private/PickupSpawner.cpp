// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupSpawner.h"
#include "Pickup.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickupSpawner::APickupSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	world = GetWorld();
	world->GetTimerManager().SetTimer(MyTimerHandle, this, &APickupSpawner::SpawnPickup, spawnInterval, true, spawnInterval);
	playerActor = world->GetFirstPlayerController()->GetPawn();
	itoaString = itoa(itoaValue, itoaBase).c_str();
}

// Called every frame
void APickupSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	playerPosition = playerActor->GetActorLocation();
	CheckPickups();
}

std::string APickupSpawner::itoa(int value, int base)
{
	const char valueToCharArray[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool isNegative = value < 0;
	bool isValidBase = base > 1 && base <= 36;
	std::string result = "";

	if (!isValidBase)
	{
		return "Invalid base!";
	}

	if (isNegative)
	{
		result += "-";
		value *= -1;
	}

	int maxExponentInValue = (int)(FMath::Log2(value) / FMath::Log2(base));
	int curExponentNumber = FMath::Pow(base, maxExponentInValue);

	for (; curExponentNumber > 0; curExponentNumber /= base)
	{
		int nCurExponentNumberInValue = (int)(value / curExponentNumber);
		value -= nCurExponentNumberInValue * curExponentNumber;
		result += valueToCharArray[nCurExponentNumberInValue];
	}

	return result;
}

APickup* APickupSpawner::GetClosetsPickup() {
	APickup* result = nullptr;

	std::list<APickup*>::iterator it;
	float shortestDistance = std::numeric_limits<float>::max();

	for (it = listPickups.begin(); it != listPickups.end(); it++)
	{
		APickup* pickup = *it;
		float currentDistance = pickup->GetDistanceTo(playerActor);

		if (currentDistance < shortestDistance)
		{
			shortestDistance = currentDistance;
			result = pickup;
		}
	}

	return result;
}

// Checks if the player is near a pickup. This should be replaced by a box-trigger with an onoverlap event
void APickupSpawner::CheckPickups()
{
	std::list<APickup*>::iterator it;
	for (it = listPickups.begin(); it != listPickups.end(); it++)
	{
		APickup* pickup = *it;
		float dist = pickup->GetDistanceTo(playerActor);

		if (dist < 100.0f)
		{
			PlaySoundAtActor(pickup->sndCollect, pickup);
			listPickups.remove(pickup);
			pickup->Destroy();
			nCollectedPickups++;
			it--;
		}
	}
}

// Get the total pickups currently in the world
int APickupSpawner::GetNPicks()
{
	if (!listPickups.empty())
	{
		return listPickups.size();
	}

	return 0;
}

// Plays a sound at the position of the given actor
void APickupSpawner::PlaySoundAtActor(USoundCue* sound, AActor* actor)
{
	FVector location = actor->GetActorLocation();
	FRotator rotation = actor->GetActorRotation();
	float pitch = FMath::RandRange(soundSettings.minPitch, soundSettings.maxPitch);
	float volume = FMath::RandRange(soundSettings.minVolume, soundSettings.maxVolume);
	UGameplayStatics::PlaySoundAtLocation(world, sound, location, rotation, volume, pitch, 0);
}

// Spawns a new pickup in the world
void APickupSpawner::SpawnPickup()
{
	if (GetNPicks() < maxPickups)
	{
		int xPos = FMath::RandRange(-1000, 1000);
		int yPos = FMath::RandRange(-1000, 1000);

		const FVector location = FVector(xPos, yPos, 200);
		const FRotator rotation = FRotator(0, 0, 0);

		int index = (int)FMath::FRandRange(0, spawnablePickups.Num());
		TSubclassOf<AActor> spawnObj = spawnablePickups[index];
		APickup* pickup = (APickup*)world->SpawnActor<AActor>(spawnObj, location, rotation);
		PlaySoundAtActor(pickup->sndSpawn, pickup);

		listPickups.push_back(pickup);
	}
}
