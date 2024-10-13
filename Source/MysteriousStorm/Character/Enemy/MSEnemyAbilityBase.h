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
	
	UFUNCTION(BlueprintCallable)
	virtual bool TryActivateAbility();
	
	UFUNCTION(BlueprintCallable)
	virtual bool CheckPrecondition();

	virtual void Update(float DeltaTime);
	bool IsActivated() const { return bIsActivated; }
	void Init(ACharacter* Owner);

	
	// 由于在行为树中ai的能力和移动是并行的，因此这里需要标记能力是否会打断移动
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInterpretMovement = false;

protected:
	bool bIsActivated;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// float Damage;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* OwnerEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	float IntervalTime;

	UPROPERTY(BlueprintReadWrite)
	float IntervalTimer;

	UFUNCTION(BlueprintCallable)
	void OnAbilityEnd();
	
	int GetIndex();
};
