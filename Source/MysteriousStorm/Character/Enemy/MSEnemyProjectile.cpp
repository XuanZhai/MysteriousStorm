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

void AMSEnemyProjectile::InitData(FVector NewPosition, int NewDamage, float NewDamageRadius)
{
	TargetPosition = NewPosition;
	auto Distance = FVector::Dist(TargetPosition, GetActorLocation());
	Time = Distance / HorizontalSpeed;
	auto VerticalSpeed = -1 * GetWorld()->GetGravityZ() * 0.5 * Time;
	ProjectileMovementComponent->Velocity = (TargetPosition - GetActorLocation()).GetSafeNormal() * HorizontalSpeed +
		FVector(0, 0, VerticalSpeed);
	ProjectileMovementComponent->Activate();
	Damage = NewDamage;
	DamageRadius = NewDamageRadius;
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
