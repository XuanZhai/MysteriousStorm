// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemData.h"
#include "MSConsumableData.generated.h"

UENUM(BlueprintType)
enum EMSConsumableType : uint8
{
	DefaultConsumable = 0,
	Health = 1 UMETA(DisplayName = "Health"),
	MoveSpeed = 2 UMETA(DisplayName = "MoveSpeed"),
	HitDamage = 3 UMETA(DisplayName = "HitDamage"),
};

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSConsumableData : public UMSItemData
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float Value;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EMSConsumableType> ConsumableType;

	UMSConsumableData();
};
