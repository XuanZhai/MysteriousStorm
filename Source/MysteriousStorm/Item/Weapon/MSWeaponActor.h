// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MediaSoundComponent.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "MysteriousStorm/Character/MSAttributeComponent.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyCharacter.h"
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
	TMap<TEnumAsByte<EMSEffect>, int> RuntimeEffects;

	// UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	// UMediaSoundComponent* MediaSoundComponent;

	UPROPERTY(EditAnywhere,meta=(AllowPrivateAccess="true"),Category="WeaponParameter")
	UNiagaraSystem* WeaponNiagaraSystem;

	UPROPERTY(EditAnywhere, Category="WeaponParameter")
	UMediaPlayer *MediaPlayer;

	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, Category="WeaponParameter")
	EWeaponType WeaponType;

	FVector RuntimeOffset;
	FVector Offset;
	bool bIsTimeStopped;

	// 基于level该种武器有多少把
	// int Level;

	int OverloadLevel;
	int CriticalLevel;
	float CurrentDamage;
	
	FMSWeaponTableRow WeaponConfig;

	UFUNCTION()
	UNiagaraComponent* SpawnNiagaraSystem(FVector Location, FRotator Rotation);

public:
	AMSWeaponActor();

	bool bIsEquipped;

	float CurrentOffsetInRound;

	// 区分该武器的表现状态是否为静态
	bool bIsStatic;

	// bool ModifyLevel(bool bIncrease);

	UFUNCTION()
	void OnBackpackOpened();
	
	UFUNCTION()
	void SetTimeStop(bool bIsTimeStop);

	void SetOwnerCharacter(ACharacter* NewOwnerCharacter);
	void ApplyEffect(EMSEffect Effect, bool bIsRemove = false);

	// 返回值确定本次遍历的攻击次数
	virtual int ProcessEffect();

	virtual void BeginPlay() override;
	virtual bool TryAttack();
	virtual void ApplyDamage();
	virtual void SearchEnemy();
	virtual void InitItemData() override;
	virtual void Tick(float DeltaSeconds) override;
};
