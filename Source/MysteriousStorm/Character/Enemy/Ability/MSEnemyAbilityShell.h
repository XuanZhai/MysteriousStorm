// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbilityBase.h"
#include "MysteriousStorm/Character/Enemy/Projectile/MSEnemyProjectile.h"
#include "MSEnemyAbilityShell.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSEnemyAbilityShell : public UMSEnemyAbilityBase
{
	GENERATED_BODY()
protected:
	virtual bool TryActivateAbility() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Ability")
	TSubclassOf<AMSEnemyProjectile> ShellClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="Ability")
	float Speed;
	
};
