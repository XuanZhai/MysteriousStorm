// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyProjectile.h"

// Sets default values
AMSEnemyProjectile::AMSEnemyProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RootComponent = ProjectileMesh;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
}

void AMSEnemyProjectile::InitData(FVector NewPosition)
{
	TargetPosition = NewPosition;
	auto Distance = FVector::Dist(TargetPosition, GetActorLocation());
	auto Time = Distance / HorizontalSpeed;
	auto VerticalSpeed = -1 * GetWorld()->GetGravityZ() * 0.5 * Time;
	ProjectileMovementComponent->Velocity = (TargetPosition - GetActorLocation()).GetSafeNormal() * HorizontalSpeed +
		FVector(0, 0, VerticalSpeed);
	ProjectileMovementComponent->Activate();
}

// Called when the game starts or when spawned
void AMSEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMSEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetPosition == GetActorLocation())
	{
		Destroy();
	}
}
