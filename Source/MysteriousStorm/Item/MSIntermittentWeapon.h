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

	const float AttackTime = 0.25;
	
#pragma endregion 

	float CurrentTime;
	bool bIsAttacking;
	float AttackProcess;
	FVector CachedAttackDirection;
	FRotator CachedAttackRotation;

	UPROPERTY()
	TArray<AMSEnemyCharacter*> SearchEnemyCache;
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual bool TryAttack() override;

	void SearchEnemy();
	
};
