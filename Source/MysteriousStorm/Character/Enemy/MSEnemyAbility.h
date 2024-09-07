// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MSEnemyAbility.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSEnemyAbility : public UObject
{
	GENERATED_BODY()
public:
	UMSEnemyAbility();
	virtual bool TryActivateAbility();
	virtual void Update(float DeltaTime);
	bool IsActivated() { return bIsActivated; }
	
protected:
	bool bIsActivated;
	
	float IntervalTime;
	float IntervalTimer;
	virtual bool CheckPrecondition() { return true; }
};
