// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSWeaponActor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyCharacter.h"
#include "MSIntermittentWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSIntermittentWeapon : public AMSWeaponActor
{
	GENERATED_BODY()

protected:
#pragma region 武器配置相关

	// UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponParameter")
	// float IntervalTime;

	float AnticipationTime = 0;
	float AttackTime = 0;

#pragma endregion

	// float WeaponIntervalTimer;
	float AttackProcessTimer;
	float AnticipationTimer;
	bool bCanBeActivated;
	// 在武器被激活后的攻击次数
	int AttackTimes;

	FVector CachedAttackPosition;
	FVector CachedAttackDirection;
	FVector CachedOwnerPosition;
	FRotator CachedAttackRotation;
	TArray<FVector> CachedAttackDirections;

	UPROPERTY(EditAnywhere, Category="WeaponParameter")
	UParticleSystem* AttackParticle;

	// UPROPERTY(EditAnywhere,BlueprintReadWrite)
	// URotatingMovementComponent* RotatingMovementComp;

	void TickAttackProcess(float DeltaSeconds);
	void OnAttackProcessEnd();

	float LastAttackTimeForDart;

public:
	AMSIntermittentWeapon();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool TryAttack() override;
	virtual void ApplyDamage() override;

	UFUNCTION()
	virtual void SearchEnemy() override;

	virtual int ProcessEffect() override;

	bool bIsAttacking;
	void ResetWeapon();
};
