// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbility.h"

UMSEnemyAbility::UMSEnemyAbility()
{
	IntervalTime = 0;
	IntervalTimer = 0;
	bIsActivated = false;
}

bool UMSEnemyAbility::TryActivateAbility_Implementation()
{
	
	return CheckPrecondition();
}


bool UMSEnemyAbility::CheckPrecondition_Implementation()
{
	if(bIsActivated)return false;
	if(IntervalTimer < IntervalTime)return false;
	return true;
}

void UMSEnemyAbility::Update(float DeltaTime)
{
	if(bIsActivated)
	{
		IntervalTimer = 0;
	}else
	{
		IntervalTimer += DeltaTime;
	}
	
}

void UMSEnemyAbility::Init(ACharacter* Owner)
{
	OwnerEnemy = Owner;
}
