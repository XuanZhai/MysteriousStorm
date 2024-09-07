// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbility.h"

UMSEnemyAbility::UMSEnemyAbility()
{
	IntervalTime = 0;
	IntervalTimer = 0;
	bIsActivated = false;
}

bool UMSEnemyAbility::TryActivateAbility()
{
	if(bIsActivated)return false;
	return CheckPrecondition();
}

void UMSEnemyAbility::Update(float DeltaTime)
{
	if(bIsActivated)
	{
		IntervalTimer += DeltaTime;
	}else
	{
		IntervalTimer = 0;
	}
	
}
