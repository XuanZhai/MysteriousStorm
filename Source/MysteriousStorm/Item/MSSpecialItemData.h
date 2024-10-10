// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemData.h"
#include "MSSpecialItemData.generated.h"

enum EMSEffect: uint8;

UENUM(BlueprintType)
enum EMSSpecialItemType : uint8
{
	DefaultSpecialItem = 0,
	Boxer = 1, // È­»÷ÊÖ
};
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSSpecialItemData : public UMSItemData
{
	GENERATED_BODY()
	
public:
	TMap<int,bool> AffectMap;

	bool bIsGridType = false;
	TEnumAsByte <EMSEffect> GridEffect;
	int32 GridEffectLevel = 1;

	TEnumAsByte<EMSSpecialItemType> SpecialItemType;
};
