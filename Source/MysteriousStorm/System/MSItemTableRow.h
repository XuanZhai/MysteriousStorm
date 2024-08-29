// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MSItemTableRow.generated.h"

class AMSItemActor;
enum EItemType : uint8;
/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FMSItemTableRow : public FTableRowBase
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AMSItemActor> AssetBP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSoftObjectPath UIPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XUISize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YUISize;

    FMSItemTableRow();
};
