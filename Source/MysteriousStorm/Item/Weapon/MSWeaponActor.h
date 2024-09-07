// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "GameFramework/Character.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "MysteriousStorm/Character/MSEnemyCharacter.h"
#include "MysteriousStorm/System/MSWeaponTableRow.h"
#include "MSWeaponActor.generated.h"


/**
 * 
 */
UCLASS(Abstract)
class MYSTERIOUSSTORM_API AMSWeaponActor : public AMSItemActor
{
	GENERATED_BODY()
protected:

	UPROPERTY()
	TArray<AMSEnemyCharacter*> SearchEnemyCache;
	
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, Category="WeaponParameter")
	EWeaponType WeaponType;

	FVector RuntimeOffset;
	FVector Offset;
	bool bIsTimeStopped;
	
	// 基于level该种武器有多少把
	int Level;
	
	FMSWeaponTableRow WeaponConfig;

public:
	AMSWeaponActor();

	// 区分该武器的表现状态是否为静态
	bool bIsStatic;
		
	bool ModifyLevel(bool bIncrease);
	void SetTimeStop(bool bIsTimeStop);
	void SetOwnerCharacter(ACharacter* NewOwnerCharacter);
	virtual void BeginPlay() override;
	void ApplyEffect(EMSEffect Effect, bool bIsRemove = false);
	
	virtual bool TryAttack();
	virtual void ApplyDamage();
	virtual void SearchEnemy();
	virtual void InitItemData() override;
	virtual void Tick(float DeltaSeconds) override;
	
};
