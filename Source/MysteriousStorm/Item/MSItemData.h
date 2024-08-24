// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MSItemData.generated.h"

class AMSItemActor;

/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XUISize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YUISize;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FSoftObjectPath PreviewUIPath;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FSoftObjectPath UIPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMSItemActor> AssetBP;

	UMSItemData();
};
