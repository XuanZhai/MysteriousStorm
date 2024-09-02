// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSWeaponActor.h"
#include "MysteriousStorm/Character/MSEnemyCharacter.h"
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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="WeaponParameter")
	float IntervalTime;
	
	float AnticipationTime = 0;
	float AttackTime = 0;
	
#pragma endregion 

	float WeaponIntervalTimer;
	float AttackProcessTimer;
	float AnticipationTimer;
	
	bool bIsAttacking;
	FVector CachedAttackPosition;
	FVector CachedAttackDirection;
	FVector CachedOwnerPosition;
	FRotator CachedAttackRotation;

	UPROPERTY()
	TArray<AMSEnemyCharacter*> SearchEnemyCache;

	void TickAttackProcess(float DeltaSeconds);
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool TryAttack() override;
	virtual void ApplyDamage()override;

	void SearchEnemy();
	
};
