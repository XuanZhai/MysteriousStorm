// Fill out your copyright notice in the Description page of Project Settings.


#include "MSGameState.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Item/MSItemActor.h"

void AMSGameState::SetGamePaused(bool NewState)
{
	bIsGamePause = NewState;

	if (OnGamePauseUpdated.IsBound())
	{
		OnGamePauseUpdated.Broadcast(bIsGamePause);
	}
}

bool AMSGameState::TrySpawnItemActorFromData(UMSItemData* InItemData, AActor* SpawnAroundTarget, AMSItemActor*& OutItemActor, bool bGroundClamp)
{
	UWorld* World = GetWorld();

	if (!InItemData || !SpawnAroundTarget || !World)
	{
		return false;
	}

	FVector SpawnLocation = SpawnAroundTarget->GetActorLocation();
	SpawnLocation = SpawnLocation + SpawnAroundTarget->GetActorForwardVector() * SpawnActorForwardOffset;
	FRotator SpawnRotator = FRotator::ZeroRotator;

	// Spawn On Ground
	if (bGroundClamp)
	{
		FHitResult HitResult;
		FVector End = SpawnLocation - FVector(0, 0, 1000);

		bool bHit = World->LineTraceSingleByChannel(HitResult, SpawnLocation, End, ECC_Visibility);

		if (bHit)
		{
			SpawnLocation = HitResult.Location;
		}
	}

	if (AActor* SpawnedActor = World->SpawnActor<AActor>(InItemData->AssetBP, SpawnLocation, SpawnRotator))
	{
		OutItemActor = Cast<AMSItemActor>(SpawnedActor);
		return IsValid(OutItemActor);
	}
	return false;
}

FSpawnItemPlan AMSGameState::GetRandomItemSpawnPlan(bool bIsEnemy) const
{
	if (bIsEnemy)
	{
		if (SpawnEnemyPlanList.Num() == 0)
		{
			return FSpawnItemPlan();
		}

		// Generate a random index
		int32 RandomIndex = FMath::RandRange(0, SpawnEnemyPlanList.Num() - 1);

		// Return the value at that index
		return SpawnEnemyPlanList[RandomIndex];
	}

	if (SpawnItemPlanList.Num() == 0)
	{
		return FSpawnItemPlan();
	}

	// Generate a random index
	int32 RandomIndex = FMath::RandRange(0, SpawnItemPlanList.Num() - 1);

	// Return the value at that index
	return SpawnItemPlanList[RandomIndex];
}