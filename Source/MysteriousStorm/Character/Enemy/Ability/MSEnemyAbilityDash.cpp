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
	if(!CheckPrecondition())
		return false;
	AMSCharacter* Enemy = Cast<AMSCharacter>(OwnerEnemy);
	AMSCharacter* Player = Cast<AMSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	bIsActivated = true;
	FVector Direction = (Player->GetActorLocation() - Enemy->GetActorLocation()).GetSafeNormal();
	TargetPosition = Enemy->GetActorLocation() + Direction * 500;
}

void UMSEnemyAbilityDash::Update(float DeltaTime)
{
	if (!bIsActivated)
	{
		IntervalTimer += DeltaTime;
	}
	else
	{
		if(TargetPosition != FVector::ZeroVector)
		{
			OwnerEnemy->SetActorLocation(FMath::VInterpTo(OwnerEnemy->GetActorLocation(), TargetPosition, DeltaTime, 1000));
		}
		if(FVector::Dist(TargetPosition, OwnerEnemy->GetActorLocation()) < 10)
		{
			bIsActivated = false;
			IntervalTimer = 0;
		}
	}
}
