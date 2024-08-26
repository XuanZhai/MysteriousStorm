// Fill out your copyright notice in the Description page of Project Settings.


#include "MSIntermittentWeapon.h"

#include "EngineUtils.h"
#include "MysteriousStorm/Character/MSEnemyCharacter.h"

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
	SearchEnemy();

	for (const auto Enemy : SearchEnemyCache)
	{
		Enemy->Hurt();
	}
	return true;
}

void AMSIntermittentWeapon::SearchEnemy()
{
	SearchEnemyCache.Empty();
	// TODO: 根据weapontype实现不同索敌算法
	TActorIterator<AMSEnemyCharacter> EnemyItr = TActorIterator<AMSEnemyCharacter>(GetWorld());
	FVector AttackDirection = OwnerCharacter->GetActorForwardVector();
	switch (WeaponType)
	{
	case EWeaponType::Sword:
		for (; EnemyItr; ++EnemyItr)
		{
			if (OverlapSectorCircle(GetActorLocation(), AttackDirection, WeaponConfig.SectorAngle, WeaponConfig.SectorRadius,
			                        EnemyItr->GetActorLocation(), 30))
			{
				SearchEnemyCache.Add(*EnemyItr);
			}
		}
		break;
	case EWeaponType::Grenade:
	case EWeaponType::ShotGun:
	case EWeaponType::MachineGun:
	case EWeaponType::Dart:
	default:
		break;
	}
}
