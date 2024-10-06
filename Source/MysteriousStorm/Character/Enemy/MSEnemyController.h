// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MSEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSEnemyController : public AAIController
{
	GENERATED_BODY()
protected:
	UFUNCTION()
	void SetEnableAI(bool bEnable);

	UPROPERTY(BlueprintReadOnly)
	bool bIsEnableAI;

	UFUNCTION()
	void OnBackpackOpened();

	UFUNCTION()
	void OnBackpackClosed();

	virtual void BeginPlay() override;
	
};
