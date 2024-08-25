// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MSWeaponTableRow.generated.h"

// enum EWeaponType : uint8;
/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FMSWeaponTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TEnumAsByte<EWeaponType> WeaponType;

	FMSWeaponTableRow();
};
