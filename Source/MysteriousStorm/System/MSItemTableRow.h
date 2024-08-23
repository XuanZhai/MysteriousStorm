// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MSItemTableRow.generated.h"

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
    FSoftObjectPath BPAssetPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSoftObjectPath PreviewUIPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSoftObjectPath UIPath;

    FMSItemTableRow();
};
