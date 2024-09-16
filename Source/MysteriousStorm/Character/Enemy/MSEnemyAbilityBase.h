// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbilityBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSEnemyAbilityBase : public UObject
{
	GENERATED_BODY()

public:
	UMSEnemyAbilityBase();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool TryActivateAbility();
	UFUNCTION(BlueprintCallable)
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* OwnerEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	float IntervalTime;

	UPROPERTY(BlueprintReadWrite)
	float IntervalTimer;

	UFUNCTION(BlueprintCallable)
	void OnAbilityEnd();
};
