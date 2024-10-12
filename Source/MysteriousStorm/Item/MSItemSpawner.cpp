// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemSpawner.h"

// Sets default values
AMSItemSpawner::AMSItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMSItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMSItemSpawner::UpdateSpawnPlan()
{
	if (bUseSelfSpawner)
	{
		return;
	}

	AGameModeBase* GameMode = GetWorld() ? GetWorld()->GetAuthGameMode<AGameModeBase>() : nullptr;
	if (AMSGameState* GS = GameMode ? Cast<AMSGameState>(GameMode->GetGameState<AMSGameState>()) : nullptr)
	{
		CurrentSpawnPlan = GS->GetRandomItemSpawnPlan(bIsEnemy);
	}
}


void AMSItemSpawner::SpawnItems()
{
	const auto& Loc = GetActorLocation();
	const auto& World = GetWorld();
	const auto& Rot = GetActorRotation();

	for (const auto& ItemPair : CurrentSpawnPlan.ItemNumPairs)
	{
		for (int32 i = 0; i < ItemPair.ItemCount; i++)
		{
			float XOffset = FMath::RandRange(-XSpawnRange, XSpawnRange);
			float YOffset = FMath::RandRange(-YSpawnRange, YSpawnRange);
			FVector SpawnLocation = FVector(Loc.X+XOffset,Loc.Y+YOffset, Loc.Z);

			AActor* SpawnedActor = World->SpawnActor<AActor>(ItemPair.ItemType, SpawnLocation, Rot);
			SpawnedActor->Tags.AddUnique(FName("FromSpawner"));
		}
	}
}

