// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSWeaponActor.h"
#include "MSIntermittentWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSIntermittentWeapon : public AMSWeaponActor
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponParameter")
	float IntervalTime;

	float CurrentTime;

	UPROPERTY()
	TArray<AActor*> SearchEnemyCache;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool TryAttack() override;

	void SearchEnemy();
	
};
