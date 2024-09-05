// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MSWeaponTableRow.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Sword,
	Hammer,
	Grenade,
	Dart,
	MachineGun,
	ShotGun,
};
/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FMSWeaponTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;

	// 武器等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	// 手雷投掷点选取范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DropDetectionRange;

	// 手雷伤害范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamageRange;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IntervalTime;

	// 扇形武器索敌扇形角度
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectorAngle;

	// 扇形武器索敌扇形半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectorRadius;

	// 攻击开始到索敌时刻的前摇时间
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AnticipationTime;

	// 攻击过程时长，对于战锤没有效果
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AttackTime;

	// 短喷每次攻击的射击次数
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 AttackAmount;

	// 飞镖检测的圆形范围
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DartDetectionRadius;

	// 飞镖的最远飞行距离
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DartMaxDistance;

	// 飞镖和战锤造成伤害的最小间隔
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MinDamageInterval;

	FMSWeaponTableRow();
};
