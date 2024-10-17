// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyProjectile.h"

#include "Kismet/GameplayStatics.h"
#include "MysteriousStorm/Character/MSCharacter.h"

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

void AMSEnemyProjectile::InitData(FVector NewPosition, int NewDamage, float NewDamageRadius,float Speed)
{
	TargetPosition = NewPosition;
	auto Distance = FVector::Dist(TargetPosition, GetActorLocation());
	HorizontalSpeed = Speed;
	Time = Distance / HorizontalSpeed;
	VerticalSpeed = -1 * GetWorld()->GetGravityZ() * 0.5 * Time;
	Damage = NewDamage;
	DamageRadius = NewDamageRadius;
	StartMove();
}

// Called when the game starts or when spawned
void AMSEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AMSEnemyProjectile::StartMove()
{
	FVector SpeedDirection = (TargetPosition - GetActorLocation()).GetSafeNormal();
	ProjectileMovementComponent->Velocity = SpeedDirection * HorizontalSpeed +
		FVector(0, 0, VerticalSpeed);
	ProjectileMovementComponent->Activate();
}

// Called every frame
void AMSEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Timer += DeltaTime;
	if (Timer >= Time)
	{
		// 播放爆炸特效
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation());
		AMSCharacter* Player = Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (FVector::Dist(Player->GetActorLocation(), GetActorLocation()) <= DamageRadius)
		{
			Player->GetAttributeComponent()->Hurt(nullptr, Damage);
		}

		Destroy();
	}
}
