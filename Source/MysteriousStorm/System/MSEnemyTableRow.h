// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyAbilityBase.h"
#include "MSEnemyTableRow.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FMSEnemyTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UMSEnemyAbilityBase>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> AbilityDamageRadius;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<float> AbilitySearchRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> AbilityDamage;
	
	FMSEnemyTableRow();
};
