// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MysteriousStorm/System/MSGameState.h"
#include "MSItemSpawner.generated.h"

UCLASS()
class MYSTERIOUSSTORM_API AMSItemSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSpawnItemPlan CurrentSpawnPlan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUseSelfSpawner = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsEnemy = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XSpawnRange = 75;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YSpawnRange = 75;

public:	
	// Sets default values for this actor's properties
	AMSItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable)
	void UpdateSpawnPlan();

	UFUNCTION(BlueprintCallable)
	void SpawnItems();
};
