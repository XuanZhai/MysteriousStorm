// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MSItemData.h"
#include "MSBackpack.generated.h"

enum EMSEffect : uint32;

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSBackpack : public UObject
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadWrite)
	UMSItemData* BackpackData;

	UPROPERTY(BlueprintReadWrite)
	TSet<UMSItemData*> Items;

public:
	void AddNewItem(UMSItemData* NewItem);

	void RemoveItem(UMSItemData* TargetItem);

	bool DoesItemExist(UMSItemData* TargetItem) const {return TargetItem && Items.Contains(TargetItem);}

	void ApplyEffect(EMSEffect Effect, float Duration = 0) {}
};
