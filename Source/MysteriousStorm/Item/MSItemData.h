// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemData.generated.h"

class UMSDataTableSubsystem;

UENUM(BlueprintType)
enum EItemType : uint8
{
	Item = 0,
	Weapon = 1,
	MAX
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct MYSTERIOUSSTORM_API FMSItemData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XUISize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YUISize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FSoftObjectPath PreviewUIPath;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FSoftObjectPath UIPath;

public:
	FMSItemData();
	~FMSItemData();
};
