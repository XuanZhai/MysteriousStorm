// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "MSGameState.generated.h"

class UMSItemData;

USTRUCT(BlueprintType)
struct FSpawnItemPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemCount = 0;
};


USTRUCT(BlueprintType)
struct FSpawnItemPlan 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FSpawnItemPair> ItemNumPairs;
};

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSGameState : public AGameStateBase
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnActorForwardOffset = 300.0f;


	UPROPERTY(BlueprintReadOnly)
	bool bIsGamePause;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSpawnItemPlan> SpawnItemPlanList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSpawnItemPlan> SpawnEnemyPlanList;

public:

	UFUNCTION(BlueprintCallable)
	bool TrySpawnItemActorFromData(UMSItemData* InItemData, AActor* SpawnAroundTarget, AMSItemActor*& OutItemActor, bool bGroundClamp = false);

	void SetGamePaused(bool NewState);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePauseUpdated, bool, NewState);
	UPROPERTY(BlueprintAssignable)
	FOnGamePauseUpdated OnGamePauseUpdated;


	FSpawnItemPlan GetRandomItemSpawnPlan(bool bIsEnemy) const;
};
