// Fill out your copyright notice in the Description page of Project Settings.


#include "MSIntermittentWeapon.h"

# pragma region lifetime

void AMSIntermittentWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentTime = 0;
}

void AMSIntermittentWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	CurrentTime += DeltaSeconds;
	if(CurrentTime >= IntervalTime)
	{
		CurrentTime -= IntervalTime;
		TryAttack();
	}
}

# pragma endregion 


bool AMSIntermittentWeapon::TryAttack()
{
	return true;
}

void AMSIntermittentWeapon::SearchEnemy()
{
	SearchEnemyCache.Empty();
}

