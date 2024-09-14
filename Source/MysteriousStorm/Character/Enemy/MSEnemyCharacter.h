// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSEnemyAbility.h"
#include "GameFramework/Character.h"
#include "MSEnemyCharacter.generated.h"

UCLASS()
class MYSTERIOUSSTORM_API AMSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMSEnemyCharacter();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	float BodyRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	float MaxHealth;

	float CurrentHealth;
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	int32 EnemyID;
	

	UPROPERTY()
	TArray<UMSEnemyAbility*> PossessAbilities;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<UMSEnemyAbility*> GetProcessAbilities() const { return PossessAbilities; }
	
	

	void Hurt(float damage);
	bool TryReadConfig();

};
