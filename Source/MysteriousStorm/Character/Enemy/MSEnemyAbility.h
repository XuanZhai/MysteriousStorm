// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSEnemyAbility : public UObject
{
	GENERATED_BODY()

public:
	UMSEnemyAbility();

	UFUNCTION(BlueprintNativeEvent)
	bool TryActivateAbility();
	virtual bool TryActivateAbility_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CheckPrecondition();
	UFUNCTION(BlueprintCallable)
	virtual bool CheckPrecondition_Implementation();

	virtual void Update(float DeltaTime);
	bool IsActivated() const { return bIsActivated; }
	void Init(ACharacter* Owner);

protected:
	bool bIsActivated;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* OwnerEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	float IntervalTime;

	UPROPERTY(BlueprintReadWrite)
	float IntervalTimer;
};
