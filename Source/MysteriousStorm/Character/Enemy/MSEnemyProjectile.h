// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MSEnemyProjectile.generated.h"

UCLASS()
class MYSTERIOUSSTORM_API AMSEnemyProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMSEnemyProjectile();
	
	void InitData(FVector NewPosition);

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

protected:
	UPROPERTY(EditAnywhere, Category="PathParameter")
	float HorizontalSpeed;

	UPROPERTY()
	FVector TargetPosition;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
