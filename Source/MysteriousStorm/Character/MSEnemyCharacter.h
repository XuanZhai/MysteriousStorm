// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MysteriousStorm/System/MSEnemyTableRow.h"
#include "MSEnemyCharacter.generated.h"

UCLASS()
class MYSTERIOUSSTORM_API AMSEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMSEnemyCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	float BodyRadius;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyParameter")
	int32 EnemyID;

	FMSEnemyTableRow EnemyConfig;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Hurt();
	bool TryReadConfig();

};
