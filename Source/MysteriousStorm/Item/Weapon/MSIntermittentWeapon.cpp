// Fill out your copyright notice in the Description page of Project Settings.


#include "MSIntermittentWeapon.h"

#include "EngineUtils.h"
#include "WeaponUtils.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyCharacter.h"
#include "MysteriousStorm/Item/Weapon/MSWeaponData.h"

# pragma region lifetime

AMSIntermittentWeapon::AMSIntermittentWeapon()
{
	// RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComp"));
	// RotatingMovementComp->Deactivate();
	bCanBeActivated = true;
}

void AMSIntermittentWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponType = WeaponConfig.WeaponType;
	AnticipationTime = WeaponConfig.AnticipationTime;
	AttackTime = WeaponConfig.AttackTime;

	bIsAttacking = false;
	CachedAttackDirection = FVector::ZeroVector;
	CachedAttackPosition = FVector::ZeroVector;
	CachedAttackRotation = FRotator::ZeroRotator;
	CachedOwnerPosition = FVector::ZeroVector;
	CachedAttackDirections.Empty();
	SearchEnemyCache.Empty();

	AttackProcessTimer = 0;
	// WeaponIntervalTimer = 0;
	AnticipationTimer = 0;

	if (WeaponType == EWeaponType::Dart)
	{
		// RotatingMovementComp->RotationRate = FRotator(0, 540, 0);
		// RotatingMovementComp->Activate();
	}
}

void AMSIntermittentWeapon::Tick(float DeltaSeconds)
{
	// TODO: 根据cd更新UI
	if(OwnerCharacter==nullptr)return;
	Super::Tick(DeltaSeconds);
	
	if (bIsTimeStopped)return;

	CurrentOffsetInRound += DeltaSeconds;
	if (CurrentOffsetInRound >= Cast<UMSWeaponData>(ItemData)->TotalRoundTime)
	{
		CurrentOffsetInRound -= Cast<UMSWeaponData>(ItemData)->TotalRoundTime;
		bCanBeActivated = true;
	}

	if (!bIsAttacking)
	{
		if (bIsStatic)
		{
			StaticMeshComp->SetVisibility(true);
		}
		else
		{
			StaticMeshComp->SetVisibility(false);
		}
		// WeaponIntervalTimer += DeltaSeconds;
		if (CurrentOffsetInRound >= Cast<UMSWeaponData>(ItemData)->TriggerTimeInRound && bCanBeActivated)
		{
			// WeaponIntervalTimer -= IntervalTime;
			AnticipationTimer = 0;
			AttackProcessTimer = 0;
			TryAttack();
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
		if (AttackProcessTimer >= AttackTime)
		{
			AttackProcessTimer = 0;
			bIsAttacking = false;
		}
		else
		{
			AttackProcessTimer += DeltaSeconds;
		}
		return;
	}
	StaticMeshComp->SetVisibility(true);
	auto Scale = StaticMeshComp->GetComponentScale();
	FVector NewLocation = FVector::ZeroVector;
	switch (WeaponType)
	{
	case EWeaponType::Sword:
		// 按照目前的攻击进度设置位置，后续攻击时间考虑给策划配置
		AttackProcessTimer += DeltaSeconds;
		
		StaticMeshComp->SetWorldScale3D(Scale);

	// 攻击流程计时
		if (AttackProcessTimer >= AttackTime)
		{
			bIsAttacking = false;
			AttackProcessTimer = 0;
			// Scale.Z = 0.2f;
			StaticMeshComp->SetWorldScale3D(FVector::OneVector*2);
		}
		else
		{
			auto OwnerLocation = OwnerCharacter->GetActorLocation();
			auto OffsetDirection = CachedAttackDirection.RotateAngleAxis(
				WeaponConfig.SectorAngle * (AttackProcessTimer / AttackTime - 0.5), FVector::UpVector);

			SetActorLocation(OwnerLocation + OffsetDirection * WeaponConfig.SectorRadius / 2);
			FRotator NewRotation = FRotator(
				180, CachedAttackRotation.Yaw + WeaponConfig.SectorAngle * (AttackProcessTimer / AttackTime - 0.5), 0);
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
	case EWeaponType::MachineGun:
		AttackProcessTimer += DeltaSeconds;
		if (AttackProcessTimer >= AttackTime)
		{
			bIsAttacking = false;
			AttackProcessTimer = 0;
		}
		else
		{
			FVector OwnerLocation = OwnerCharacter->GetActorLocation();
			SetActorLocation(OwnerLocation + CachedAttackDirection * 100);
		}
		break;
	case EWeaponType::Dart:
		AttackProcessTimer += DeltaSeconds;

		if (AttackProcessTimer <= AttackTime / 2)
		{
			NewLocation = FMath::Lerp(CachedOwnerPosition,
			                          CachedOwnerPosition + CachedAttackDirection * WeaponConfig.DartMaxDistance,
			                          AttackProcessTimer / AttackTime * 2);
		}
		else if (AttackProcessTimer <= AttackTime)
		{
			NewLocation = FMath::Lerp(CachedOwnerPosition + CachedAttackDirection * WeaponConfig.DartMaxDistance,
			                          OwnerCharacter->GetActorLocation(),
			                          (AttackProcessTimer / AttackTime - 0.5) * 2);
		}
		else
		{
			bIsAttacking = false;
			AttackProcessTimer = 0;
		}
		SetActorLocation(NewLocation);
		break;
	case EWeaponType::ShotGun:
		AttackProcessTimer += DeltaSeconds;
		if (AttackProcessTimer >= AttackTime)
		{
			bIsAttacking = false;
			AttackProcessTimer = 0;
		}
		else
		{
			FVector OwnerLocation = OwnerCharacter->GetActorLocation();
			SetActorLocation(OwnerLocation + CachedAttackDirection[0] * 100);
		}
		break;
	default:
		break;
	}

	// 飞镖武器不参与统一计时
	if (WeaponType != EWeaponType::Dart)
	{
		// 攻击前摇计时
		if (AnticipationTimer >= AnticipationTime)return;
		AnticipationTimer += DeltaSeconds;
		if (AnticipationTimer >= AnticipationTime)
		{
			ApplyDamage();
		}
	}
}


# pragma endregion

# pragma region event

bool AMSIntermittentWeapon::TryAttack()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("weapon attack"));
	bIsAttacking = true;
	bCanBeActivated = false;
	CachedAttackDirection = OwnerCharacter->GetActorForwardVector();
	CachedAttackRotation = OwnerCharacter->GetActorRotation();
	CachedOwnerPosition = OwnerCharacter->GetActorLocation();
	if (WeaponType == EWeaponType::Grenade)
	{
		// 生成随机手雷落点
		float RandomRadius = FMath::RandRange(0.0f, WeaponConfig.DropDetectionRange);
		float RandomAngle = FMath::RandRange(0.0f, 360.0f);
		CachedAttackPosition = OwnerCharacter->GetActorLocation() +
			FVector(RandomRadius * FMath::Cos(RandomAngle), RandomRadius * FMath::Sin(RandomAngle),
			        0);
	}
	if (WeaponType == EWeaponType::ShotGun)
	{
		// 生成随机的射击角度
		// TODO: 需要问问策划是否需要不重叠
		CachedAttackDirections.Empty();
		for (int i = 0; i < WeaponConfig.AttackAmount; i++)
		{
			float RandomAngle = FMath::RandRange(-180, 180);
			FVector AttackDirection = CachedAttackDirection.RotateAngleAxis(RandomAngle, FVector::UpVector);
			CachedAttackDirections.Add(AttackDirection);
		}
	}
	return true;
}

void AMSIntermittentWeapon::ApplyDamage()
{
	if (bIsStatic)return;
	SearchEnemy();
	for (const auto Enemy : SearchEnemyCache)
	{
		Enemy->Hurt(Cast<UMSWeaponData>(ItemData)->Damage);
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
	case EWeaponType::MachineGun:
	case EWeaponType::Sword:
		// 基于扇形检测
		// DrawDebugLine(GetWorld(), AttackStart,
		//               AttackStart + AttackDirection.RotateAngleAxis(-WeaponConfig.SectorAngle / 2, FVector::UpVector) *
		//               WeaponConfig.SectorRadius,
		//               FColor::Green, false, 1.0f, 0, 1);
		// DrawDebugLine(GetWorld(), AttackStart,
		//               AttackStart + AttackDirection.RotateAngleAxis(WeaponConfig.SectorAngle / 2, FVector::UpVector) *
		//               WeaponConfig.SectorRadius,
		//               FColor::Green, false, 1.0f, 0, 1);
		// DrawDebugCircle(GetWorld(), AttackStart, WeaponConfig.SectorRadius, 100, FColor::Red, false, 1.0f, 0, 1,
		//                 FVector::RightVector, FVector::ForwardVector);

		for (; EnemyItr; ++EnemyItr)
		{
			// TODO: 怪物半径需要后续配置
			if (WeaponUtils::OverlapSectorCircle(AttackStart, AttackDirection, WeaponConfig.SectorAngle,
			                                     WeaponConfig.SectorRadius,
			                                     EnemyItr->GetActorLocation(), 100))
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
			if (WeaponUtils::OverlapCircleCircle(CachedAttackPosition, WeaponConfig.DamageRange,
			                                     EnemyItr->GetActorLocation(), 100))
			{
				SearchEnemyCache.Add(*EnemyItr);
			}
		}

	case EWeaponType::ShotGun:
		// 基于多个扇形检测
		// TODO: 需要确定同一个敌人是否会被两个扇形同时伤害到
		DrawDebugCircle(GetWorld(), AttackStart, WeaponConfig.SectorRadius, 100, FColor::Red, false, 1.0f, 0, 1,
		                FVector::RightVector, FVector::ForwardVector);
		for (auto direction : CachedAttackDirections)
		{
			DrawDebugLine(GetWorld(), AttackStart,
			              AttackStart + direction.RotateAngleAxis(-WeaponConfig.SectorAngle / 2, FVector::UpVector) *
			              WeaponConfig.SectorRadius, FColor::Green, false, 1.0f, 0, 1);
			DrawDebugLine(GetWorld(), AttackStart,
			              AttackStart + direction.RotateAngleAxis(WeaponConfig.SectorAngle / 2, FVector::UpVector) *
			              WeaponConfig.SectorRadius, FColor::Green, false, 1.0f, 0, 1);
			for (; EnemyItr; ++EnemyItr)
			{
				// TODO: 怪物半径需要后续配置
				if (WeaponUtils::OverlapSectorCircle(AttackStart, direction, WeaponConfig.SectorAngle,
				                                     WeaponConfig.SectorRadius,
				                                     EnemyItr->GetActorLocation(), 100))
				{
					if (SearchEnemyCache.Contains(*EnemyItr))continue;
					SearchEnemyCache.Add(*EnemyItr);
				}
			}
		}


	case EWeaponType::Dart:
		for (; EnemyItr; ++EnemyItr)
		{
			// TODO: 怪物半径需要后续配置
			if (WeaponUtils::OverlapCircleCircle(GetActorLocation(), WeaponConfig.DartDetectionRadius,
			                                     EnemyItr->GetActorLocation(), 10))
			{
				if (SearchEnemyCache.Contains(*EnemyItr))continue;
				SearchEnemyCache.Add(*EnemyItr);
			}
		}
	default:
		break;
	}
}
# pragma endregion
