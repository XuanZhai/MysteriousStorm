// Fill out your copyright notice in the Description page of Project Settings.


#include "MSIntermittentWeapon.h"

#include "EngineUtils.h"
#include "MysteriousStorm/Character/MSEnemyCharacter.h"

# pragma region lifetime

void AMSIntermittentWeapon::BeginPlay()
{
	Super::BeginPlay();
	CurrentTime = 0;
	IntervalTime = WeaponConfig.IntervalTime;
	WeaponType = WeaponConfig.WeaponType;
	bIsAttacking = false;
	AttackProcess = 0;
	CachedAttackDirection = FVector::ZeroVector;
}

void AMSIntermittentWeapon::Tick(float DeltaSeconds)
{
	// TODO: 根据cd更新UI
	Super::Tick(DeltaSeconds);
	if(bIsTimeStopped)return;
	
	if (!bIsAttacking)
	{
		if(bIsStatic)
		{
			StaticMeshComp->SetVisibility(true);
		}else
		{
			
			StaticMeshComp->SetVisibility(false);
			CurrentTime += DeltaSeconds;
			if (CurrentTime >= IntervalTime)
			{
				CurrentTime -= IntervalTime;
				TryAttack();
			}
		}
	}
	else
	{
		if(bIsStatic)
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
			AttackProcess += DeltaSeconds / AttackTime;
			
			Scale.Z = WeaponConfig.SectorRadius / 200;
			StaticMeshComp->SetWorldScale3D(Scale);
			if (AttackProcess >= 1)
			{
				bIsAttacking = false;
				AttackProcess = 0;
				Scale.Z = 0.2f;
				StaticMeshComp->SetWorldScale3D(Scale);
			}
			else
			{
				auto OwnerLocation = OwnerCharacter->GetActorLocation();
				auto OffsetDirection = CachedAttackDirection.RotateAngleAxis(WeaponConfig.SectorAngle * (AttackProcess - 0.5), FVector::UpVector);

				SetActorLocation(OwnerLocation + OffsetDirection * WeaponConfig.SectorRadius / 2);
				FRotator NewRotation = FRotator(90, CachedAttackRotation.Yaw + WeaponConfig.SectorAngle * (AttackProcess - 0.5), 0);
				SetActorRotation(NewRotation);
			}
			break;
		default:
			bIsAttacking = false;
			break;
		}
	}
}

# pragma endregion


bool AMSIntermittentWeapon::TryAttack()
{
	SearchEnemy();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString("暴风巨剑索敌攻击"));
	bIsAttacking = true;
	CachedAttackDirection = OwnerCharacter->GetActorForwardVector();
	CachedAttackRotation = OwnerCharacter->GetActorRotation();
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
	FVector AttackStart = OwnerCharacter->GetActorLocation();


	switch (WeaponType)
	{
	case EWeaponType::Sword:
		// 基于扇形检测
		DrawDebugLine(GetWorld(), AttackStart,
		              AttackStart + AttackDirection.RotateAngleAxis(-WeaponConfig.SectorAngle / 2, FVector::UpVector) * WeaponConfig.SectorRadius,
		              FColor::Green, false, 1.0f, 0, 1);
		DrawDebugLine(GetWorld(), AttackStart,
		              AttackStart + AttackDirection.RotateAngleAxis(WeaponConfig.SectorAngle / 2, FVector::UpVector) * WeaponConfig.SectorRadius,
		              FColor::Green, false, 1.0f, 0, 1);
		DrawDebugCircle(GetWorld(), AttackStart, WeaponConfig.SectorRadius, 100, FColor::Red, false, 1.0f, 0, 1, FVector::RightVector,
		                FVector::ForwardVector);

		for (; EnemyItr; ++EnemyItr)
		{
			// TODO: 怪物半径需要后续配置
			if (OverlapSectorCircle(OwnerCharacter->GetActorLocation(), AttackDirection, WeaponConfig.SectorAngle, WeaponConfig.SectorRadius,
			                        EnemyItr->GetActorLocation(), 10))
			{
				SearchEnemyCache.Add(*EnemyItr);
			}
		}
		break;
	case EWeaponType::Grenade:
	// 基于范围内随机生成的圆形区域检测

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
