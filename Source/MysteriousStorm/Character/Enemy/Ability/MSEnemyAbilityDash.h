// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbilityBase.h"
#include "MSEnemyAbilityDash.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSEnemyAbilityDash : public UMSEnemyAbilityBase
{
	GENERATED_BODY()
public:
	UMSEnemyAbilityDash();
protected:
	virtual bool CheckPrecondition() override;
	virtual bool TryActivateAbility() override;
	virtual void Update(float DeltaTime) override;

	FVector TargetPosition;

	UPROPERTY(EditAnywhere,Category="Ability Parameter")
	float Speed = 3;

	bool HasHurtPlayer = false;
};
