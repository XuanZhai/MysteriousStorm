// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbilityDash.h"

#include "Kismet/GameplayStatics.h"
#include "MysteriousStorm/Character/MSCharacter.h"

UMSEnemyAbilityDash::UMSEnemyAbilityDash()
{
	bInterruptMovement = true;
	TargetPosition = FVector::ZeroVector;
}

bool UMSEnemyAbilityDash::CheckPrecondition()
{
	return Super::CheckPrecondition();
}

bool UMSEnemyAbilityDash::TryActivateAbility()
{
	if (!CheckPrecondition())
		return false;
	AMSEnemyCharacter* Enemy = Cast<AMSEnemyCharacter>(OwnerEnemy);
	AMSCharacter* Player = Cast<AMSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	bIsActivated = true;
	FVector Direction = (Player->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal();
	TargetPosition = Enemy->GetActorLocation() + Direction * 1000;
	return true;
}

void UMSEnemyAbilityDash::Update(float DeltaTime)
{
	if (!bIsActivated)
	{
		IntervalTimer += DeltaTime;
	}
	else
	{
		if (TargetPosition != FVector::ZeroVector)
		{
			OwnerEnemy->SetActorLocation(
				FMath::VInterpConstantTo(OwnerEnemy->GetActorLocation(), TargetPosition, DeltaTime, Speed));
		}
		AMSEnemyCharacter* EnemyPlayer = Cast<AMSEnemyCharacter>(OwnerEnemy);
		if (!HasHurtPlayer && FVector::Dist(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),
		                                    OwnerEnemy->GetActorLocation()) < EnemyPlayer->GetEnemyConfig()->
			AbilityDamageRadius[GetIndex()])
		{
			AMSCharacter* Player = Cast<AMSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			Player->GetAttributeComponent()->Hurt(OwnerEnemy, EnemyPlayer->GetEnemyConfig()->AbilityDamage[GetIndex()]);
			HasHurtPlayer = true;
		}
		if (FVector::Dist(TargetPosition, OwnerEnemy->GetActorLocation()) < 10)
		{
			bIsActivated = false;
			IntervalTimer = 0;
			HasHurtPlayer = false;
		}
	}
}
