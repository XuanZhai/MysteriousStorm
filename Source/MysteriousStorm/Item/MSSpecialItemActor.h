// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemActor.h"
#include "MSSpecialItemActor.generated.h"

enum EMSSpecialItemType : uint8;
enum EMSEffect : uint8;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSSpecialItemActor : public AMSItemActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TMap<int, bool> AffectMap;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EMSSpecialItemType> SpecialItemType;

	UPROPERTY(EditDefaultsOnly)
	bool bIsGridType = false;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte <EMSEffect> GridEffect;

	UPROPERTY(EditDefaultsOnly)
	int32 GridEffectLevel;

	virtual void InitItemData() override;
};
