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
	if (CurrentTime >= IntervalTime)
	{
		CurrentTime -= IntervalTime;
		TryAttack();
	}
}

# pragma endregion


bool AMSIntermittentWeapon::TryAttack()
{
	// TODO: 根据weapontype实现不同索敌算法
	switch (WeaponType)
	{
	case EWeaponType::Sword:
	case EWeaponType::Grenade:
	case EWeaponType::ShotGun:
	case EWeaponType::MachineGun:
	case EWeaponType::Dart:
	default:
		break;
	}
	return true;
}

void AMSIntermittentWeapon::SearchEnemy()
{
	SearchEnemyCache.Empty();
}
