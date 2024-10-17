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

	virtual void InitData(FVector NewPosition, int NewDamage, float NewDamageRadius,float Speed);

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplosionParticle;

protected:
	float VerticalSpeed;
	float HorizontalSpeed;

	UPROPERTY()
	FVector TargetPosition;

	UPROPERTY(BlueprintReadWrite)
	int Damage;

	UPROPERTY(BlueprintReadWrite)
	float DamageRadius;

	float Time;
	float Timer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void StartMove();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
