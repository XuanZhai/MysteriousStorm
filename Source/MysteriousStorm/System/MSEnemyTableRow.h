// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
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
	
	FMSEnemyTableRow();
};
