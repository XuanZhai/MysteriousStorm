// Fill out your copyright notice in the Description page of Project Settings.


#include "MSIntermittentWeapon.h"

#include "EngineUtils.h"
#include "MysteriousStorm/Character/MSEnemyCharacter.h"

# pragma region lifetime


void AMSIntermittentWeapon::BeginPlay()
{
	Super::BeginPlay();

	IntervalTime = WeaponConfig.IntervalTime;
	WeaponType = WeaponConfig.WeaponType;
	bIsAttacking = false;
	CachedAttackDirection = FVector::ZeroVector;
	CachedAttackPosition = FVector::ZeroVector;
	CachedAttackRotation = FRotator::ZeroRotator;
	CachedOwnerPosition = FVector::ZeroVector;
	AttackProcessTimer = 0;
	WeaponIntervalTimer = 0;
	AnticipationTimer = 0;
}

void AMSIntermittentWeapon::Tick(float DeltaSeconds)
{
	// TODO: 根据cd更新UI
	Super::Tick(DeltaSeconds);
	if (bIsTimeStopped)return;

	if (!bIsAttacking)
	{
		if (bIsStatic)
		{
			StaticMeshComp->SetVisibility(true);
		}
		else
		{
			StaticMeshComp->SetVisibility(false);
			WeaponIntervalTimer += DeltaSeconds;
			if (WeaponIntervalTimer >= IntervalTime)
			{
				WeaponIntervalTimer -= IntervalTime;
				AnticipationTimer = 0;
				AttackProcessTimer = 0;
				TryAttack();
			}
		}
	}
	else
	{
		TickAttackProcess(DeltaSeconds);
	}
}

void AMSIntermittentWeapon::TickAttackProcess(float DeltaSeconds)
{
	if (bIsStatic)
	{
		StaticMeshComp->SetVisibility(false);
		return;
	}
	StaticMeshComp->SetVisibility(true);
	auto Scale = StaticMeshComp->GetComponentScale();
	switch (WeaponType)
	{
	case EWeaponType::Sword:
		// 按照目前的攻击进度设置位置，后续攻击时间考虑给策划配置
		AttackProcessTimer += DeltaSeconds;

		Scale.Z = WeaponConfig.SectorRadius / 200;
		StaticMeshComp->SetWorldScale3D(Scale);

	// 攻击流程计时
		if (AttackProcessTimer >= AttackTime)
		{
			bIsAttacking = false;
			AttackProcessTimer = 0;
			Scale.Z = 0.2f;
			StaticMeshComp->SetWorldScale3D(Scale);
		}
		else
		{
			auto OwnerLocation = OwnerCharacter->GetActorLocation();
			auto OffsetDirection = CachedAttackDirection.RotateAngleAxis(
				WeaponConfig.SectorAngle * (AttackProcessTimer / AttackTime - 0.5), FVector::UpVector);

			SetActorLocation(OwnerLocation + OffsetDirection * WeaponConfig.SectorRadius / 2);
			FRotator NewRotation = FRotator(
				90, CachedAttackRotation.Yaw + WeaponConfig.SectorAngle * (AttackProcessTimer / AttackTime - 0.5), 0);
			SetActorRotation(NewRotation);
		}
		break;
	case EWeaponType::Grenade:
		AttackProcessTimer += DeltaSeconds;
		if (AttackProcessTimer >= AttackTime)
		{
			bIsAttacking = false;
			AttackProcessTimer = 0;
		}
		else
		{
			FVector HorizontalPosition = FMath::Lerp(CachedOwnerPosition, CachedAttackPosition,
			                                         AttackProcessTimer / AttackTime);
			// 基于10的重力加速度计算此刻抛物线的高度
			float Height = 10 * 0.5 * AttackProcessTimer * (AttackTime - AttackProcessTimer) * 100;
			SetActorLocation(FVector(HorizontalPosition.X, HorizontalPosition.Y, Height + CachedOwnerPosition.Z));
		}
		break;

	default:
		break;
	}

	// 攻击前摇计时
	if (AnticipationTimer >= AnticipationTime)return;
	AnticipationTimer += DeltaSeconds;
	if (AnticipationTimer >= AnticipationTime)
	{
		ApplyDamage();
	}
}

# pragma endregion

# pragma region event
#pragma optimize("", off)

bool AMSIntermittentWeapon::TryAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("weapon attack"));
	bIsAttacking = true;
	CachedAttackDirection = OwnerCharacter->GetActorForwardVector();
	CachedAttackRotation = OwnerCharacter->GetActorRotation();
	if (WeaponType == EWeaponType::Grenade)
	{
		// 生成随机手雷落点
		float RandomRadius = FMath::RandRange(0.0f, WeaponConfig.DropDetectionRange);
		float RandomAngle = FMath::RandRange(0.0f, 360.0f);
		CachedAttackPosition = OwnerCharacter->GetActorLocation() +
			FVector(RandomRadius * FMath::Cos(RandomAngle), RandomRadius * FMath::Sin(RandomAngle),
			        0);
		CachedOwnerPosition = OwnerCharacter->GetActorLocation();
	}
	return true;
}

void AMSIntermittentWeapon::ApplyDamage()
{
	SearchEnemy();
	for (const auto Enemy : SearchEnemyCache)
	{
		Enemy->Hurt();
	}
}

void AMSIntermittentWeapon::SearchEnemy()
{
	SearchEnemyCache.Empty();
	// TODO: 根据weapontype实现不同索敌算法
	TActorIterator<AMSEnemyCharacter> EnemyItr = TActorIterator<AMSEnemyCharacter>(GetWorld());
	FVector AttackDirection = OwnerCharacter->GetActorForwardVector();
	FVector AttackStart = OwnerCharacter->GetActorLocation();


	switch (WeaponType)
	{
	case EWeaponType::Sword:
		// 基于扇形检测
		DrawDebugLine(GetWorld(), AttackStart,
		              AttackStart + AttackDirection.RotateAngleAxis(-WeaponConfig.SectorAngle / 2, FVector::UpVector) *
		              WeaponConfig.SectorRadius,
		              FColor::Green, false, 1.0f, 0, 1);
		DrawDebugLine(GetWorld(), AttackStart,
		              AttackStart + AttackDirection.RotateAngleAxis(WeaponConfig.SectorAngle / 2, FVector::UpVector) *
		              WeaponConfig.SectorRadius,
		              FColor::Green, false, 1.0f, 0, 1);
		DrawDebugCircle(GetWorld(), AttackStart, WeaponConfig.SectorRadius, 100, FColor::Red, false, 1.0f, 0, 1,
		                FVector::RightVector, FVector::ForwardVector);

		for (; EnemyItr; ++EnemyItr)
		{
			// TODO: 怪物半径需要后续配置
			if (OverlapSectorCircle(AttackStart, AttackDirection, WeaponConfig.SectorAngle,
			                        WeaponConfig.SectorRadius,
			                        EnemyItr->GetActorLocation(), 10))
			{
				SearchEnemyCache.Add(*EnemyItr);
			}
		}
		break;
	case EWeaponType::Grenade:
		// 基于范围内随机生成的圆形区域检测

		DrawDebugSphere(GetWorld(), CachedAttackPosition, WeaponConfig.DamageRange, 100, FColor::Red, false, 10.0f, 0,
		                1);
		for (; EnemyItr; ++EnemyItr)
		{
			if (OverlapCircleCircle(CachedAttackPosition, WeaponConfig.DamageRange, EnemyItr->GetActorLocation(), 10))
			{
				SearchEnemyCache.Add(*EnemyItr);
			}
		}


	case EWeaponType::ShotGun:
	// 基于多个扇形检测
	case EWeaponType::MachineGun:
	// 基于扇形检测
	case EWeaponType::Dart:
		// 基于举行检测
	default:
		break;
	}
}
# pragma endregion
