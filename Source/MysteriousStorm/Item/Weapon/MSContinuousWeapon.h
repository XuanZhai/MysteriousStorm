// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSWeaponActor.h"
#include "MSContinuousWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSContinuousWeapon : public AMSWeaponActor
{
	GENERATED_BODY()

protected:
	float IntervalTimer;
	float OffsetLength = 200.0f;
	float CurrentYaw = 0;
	float RotatingRate = 100.0f;
	FVector Offset = FVector(OffsetLength,0,0);
	
	
public:
	
	virtual void BeginPlay() override;
	virtual void ApplyDamage() override;
	virtual void SearchEnemy() override;
	virtual void Tick(float DeltaSeconds) override;
};
