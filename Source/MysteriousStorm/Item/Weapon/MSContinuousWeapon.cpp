// Fill out your copyright notice in the Description page of Project Settings.


#include "MSContinuousWeapon.h"

#include "EngineUtils.h"


void AMSContinuousWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (bIsStatic)
	{
		StaticMeshComp->SetVisibility(false);
	}else
	{
		StaticMeshComp->SetVisibility(true);
	}
	IntervalTimer = 0;
	Offset = FVector(OffsetLength, 0, 0);
}

void AMSContinuousWeapon::ApplyDamage()
{
	SearchEnemyCache.Empty();
	SearchEnemy();
	for (auto Enemy : SearchEnemyCache)
	{
		Enemy->Hurt();
	}
}

void AMSContinuousWeapon::SearchEnemy()
{
	TActorIterator<AMSEnemyCharacter> EnemyItr = TActorIterator<AMSEnemyCharacter>(GetWorld());
	for (; EnemyItr; ++EnemyItr)
	{
		AMSEnemyCharacter* Enemy = *EnemyItr;
		FVector EnemyLocation = Enemy->GetActorLocation();
		if (OverlapCircleCircle(OwnerCharacter->GetActorLocation(), WeaponConfig.DamageRange, EnemyLocation, 100))
		{
			SearchEnemyCache.Add(Enemy);
		}
	}
}

void AMSContinuousWeapon::Tick(float DeltaSeconds)
{
	if (bIsStatic)return;
	Super::Tick(DeltaSeconds);
	// 目前应该只有蒸汽重锤一个武器
	IntervalTimer += DeltaSeconds;
	if (IntervalTimer >= WeaponConfig.IntervalTime)
	{
		IntervalTimer -= WeaponConfig.IntervalTime;
		ApplyDamage();
	}
	CurrentYaw += RotatingRate * DeltaSeconds;
	FVector CurrentOffset = Offset.RotateAngleAxis(CurrentYaw, FVector(0, 0, 1));
	SetActorLocation(OwnerCharacter->GetActorLocation() + CurrentOffset);
}
