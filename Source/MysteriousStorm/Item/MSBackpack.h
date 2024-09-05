// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MSItemData.h"
#include "MSBackpack.generated.h"
/**
 * 
 */
enum EMSEffect : uint8;

UCLASS()
class MYSTERIOUSSTORM_API UMSBackpack : public UObject
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(BlueprintReadWrite)
	UMSItemData* BackpackData;

	UPROPERTY(BlueprintReadWrite)
	TSet<UMSItemData*> Items;

	UPROPERTY(BlueprintReadWrite)
	TSet<TEnumAsByte<EMSEffect>> Effects;

public:
	void SetBagData(UMSItemData* NewBag) {BackpackData = NewBag; }

	void AddNewItem(UMSItemData* NewItem);

	void RemoveItem(UMSItemData* TargetItem);

	bool DoesItemExist(UMSItemData* TargetItem) const {return TargetItem && Items.Contains(TargetItem);}

	void AddEffect(EMSEffect NewEffect);

	void RemoveEffect(EMSEffect TargetEffect);

	bool DoesEffectExist(EMSEffect TargetEffect) const { return Effects.Contains(TargetEffect); }

	UMSItemData* GetBagData() const {return BackpackData; }
};
