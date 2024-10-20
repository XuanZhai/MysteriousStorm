// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MSBTDecoratorDistance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSBTDecoratorDistance : public UBTDecorator
{
	GENERATED_BODY()
public:
	UMSBTDecoratorDistance();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="AI 参数")
	float MaxDistance;
};
