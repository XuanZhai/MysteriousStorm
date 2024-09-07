// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemData.h"
#include "MSWeaponData.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSWeaponData : public UMSItemData
{
	GENERATED_BODY()
public:
	// 目前只存储可以通过effect修改的属性
	float Damage;

	UMSWeaponData();
	
};
