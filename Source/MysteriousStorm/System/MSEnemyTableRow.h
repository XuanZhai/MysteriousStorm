// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyAbility.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyCharacter.h"
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
	TArray<TSubclassOf<UMSEnemyAbility>> Abilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMSEnemyCharacter> EnemyBP;
	
	FMSEnemyTableRow();
};
