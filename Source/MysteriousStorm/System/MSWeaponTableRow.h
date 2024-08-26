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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString WeaponName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float IntervalTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectorAngle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SectorRadius;

	FMSWeaponTableRow();
};
