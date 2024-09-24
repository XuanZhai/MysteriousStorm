// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbilityBase.h"
#include "MSEnemyAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSEnemyAbility : public UMSEnemyAbilityBase
{
	GENERATED_BODY()
public:
	virtual bool TryActivateAbility_Implementation() override;
	virtual bool CheckPrecondition_Implementation() override;
	
};
