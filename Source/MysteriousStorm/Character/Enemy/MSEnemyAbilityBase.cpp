// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbilityBase.h"

UMSEnemyAbilityBase::UMSEnemyAbilityBase()
{
	IntervalTime = 0;
	IntervalTimer = 0;
	bIsActivated = false;
}

bool UMSEnemyAbilityBase::TryActivateAbility_Implementation()
{
	if (CheckPrecondition_Implementation())
	{
		bIsActivated = true;
		IntervalTimer = 0;
		return true;
	}
	return false;
}


bool UMSEnemyAbilityBase::CheckPrecondition_Implementation()
{
	if (bIsActivated)return false;
	if (IntervalTimer < IntervalTime)return false;
	return true;
}

void UMSEnemyAbilityBase::Update(float DeltaTime)
{
	if (bIsActivated)
	{
		IntervalTimer = 0;
		bIsActivated = false;
	}
	else
	{
		IntervalTimer += DeltaTime;
	}
}

void UMSEnemyAbilityBase::Init(ACharacter* Owner)
{
	OwnerEnemy = Owner;
}

void UMSEnemyAbilityBase::OnAbilityEnd()
{
	bIsActivated = false;
}

