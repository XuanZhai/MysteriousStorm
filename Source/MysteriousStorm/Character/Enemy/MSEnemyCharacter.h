// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability/MSEnemyAbilityBase.h"
#include "MysteriousStorm/System/MSEnemyTableRow.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "MysteriousStorm/UI/MSHealthBarWidget.h"
#include "MSEnemyCharacter.generated.h"

UCLASS()
class MYSTERIOUSSTORM_API AMSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMSEnemyCharacter();
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	UParticleSystem* HurtParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	UParticleSystem* DeadParticle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UWidgetComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	TSubclassOf<UMSHealthBarWidget> HealthBarWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	float BodyRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float CurrentHealth;
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	int32 EnemyID;
	
	UPROPERTY()
	TArray<UMSEnemyAbilityBase*> PossessAbilities;

	bool bIsAbilityActive;
	FMSEnemyTableRow EnemyConfig;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<UMSEnemyAbilityBase*> GetProcessAbilities() const { return PossessAbilities; }

	UFUNCTION(BlueprintCallable)
	void Hurt(float damage, bool bPlayHurtParticle = true);
	bool TryReadConfig();

	TArray<UMSEnemyAbilityBase*> GetAbilities() const { return PossessAbilities; }
	FMSEnemyTableRow* GetEnemyConfig() { return &EnemyConfig; }

};
