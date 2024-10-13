// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbilityBase.h"
#include "MSEnemyProjectile.h"
#include "MSEnemyAbilityProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSEnemyAbilityProjectile : public UMSEnemyAbilityBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Ability")
	TSubclassOf<AMSEnemyProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Ability")
	float SearchRange;

public:
	virtual bool TryActivateAbility() override;
	virtual bool CheckPrecondition() override;
};
