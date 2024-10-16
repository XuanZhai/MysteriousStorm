// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyProjectile.h"
#include "MSEnemyShell.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSEnemyShell : public AMSEnemyProjectile
{
	GENERATED_BODY()
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
public:
	virtual void InitData(FVector NewPosition, int NewDamage, float NewDamageRadius, float Speed) override;
};
