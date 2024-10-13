// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "MSAudioTableRow.generated.h"

UENUM(BlueprintType)
enum class EAudioType : uint8
{
	Default,
};

USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FMSAudioTableRow : public FTableRowBase
{
	GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CorrespondingItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAudioType AudioType;
	
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Sound;

    FMSAudioTableRow();
};
