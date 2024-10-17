// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyShell.h"

#include "MysteriousStorm/Character/MSCharacter.h"


void AMSEnemyShell::Tick(float DeltaSeconds)
{
	Timer += DeltaSeconds;
	AMSCharacter* Player = Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (FVector::Dist(Player->GetActorLocation(), GetActorLocation()) <= DamageRadius)
	{
		Player->GetAttributeComponent()->Hurt(nullptr, Damage);
	}
	if (Timer >= Time)
	{
		Destroy();
	}
}

void AMSEnemyShell::BeginPlay()
{
	ProjectileMovementComponent->ProjectileGravityScale = 0;
	Super::BeginPlay();
}

void AMSEnemyShell::InitData(FVector NewPosition, int NewDamage, float NewDamageRadius, float Speed)
{
	TargetPosition = NewPosition;
	auto Distance = FVector::Dist(TargetPosition, GetActorLocation());
	HorizontalSpeed = Speed;
	Time = Distance / HorizontalSpeed;
	VerticalSpeed = 0;
	Damage = NewDamage;
	DamageRadius = NewDamageRadius;
	StartMove();
}
