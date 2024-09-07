// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemActor.h"
#include "MSConsumableActor.generated.h"

enum EMSConsumableType : uint8;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSConsumableActor : public AMSItemActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly)
	float Value;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EMSConsumableType> ConsumableType;

	virtual void InitItemData() override;

public:
	AMSConsumableActor();
};
