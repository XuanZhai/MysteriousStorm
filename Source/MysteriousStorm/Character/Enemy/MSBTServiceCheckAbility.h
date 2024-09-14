// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MSBTServiceCheckAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSBTServiceCheckAbility : public UBTService
{
	GENERATED_BODY()
public:
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
