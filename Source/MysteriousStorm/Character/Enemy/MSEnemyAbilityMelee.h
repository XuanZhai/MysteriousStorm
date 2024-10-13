// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbilityBase.h"
#include "MSEnemyAbilityMelee.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSEnemyAbilityMelee : public UMSEnemyAbilityBase
{
	GENERATED_BODY()
public:
	virtual bool TryActivateAbility() override;
	virtual bool CheckPrecondition() override;
	
	
};
