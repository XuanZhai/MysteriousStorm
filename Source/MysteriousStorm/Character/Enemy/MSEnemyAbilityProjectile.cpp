// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbilityProjectile.h"

#include "MSEnemyCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool UMSEnemyAbilityProjectile::TryActivateAbility()
{
	if (CheckPrecondition())
	{
		auto Projectile = GetWorld()->SpawnActor<AMSEnemyProjectile>(ProjectileClass, OwnerEnemy->GetActorLocation(),
		                                                             OwnerEnemy->GetActorRotation(),
		                                                             FActorSpawnParameters());
		AMSEnemyCharacter* Enemy = Cast<AMSEnemyCharacter>(OwnerEnemy);
		int index = GetIndex();
		Projectile->InitData(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation(),
		                     Enemy->GetEnemyConfig()->AbilityDamage[index],
		                     Enemy->GetEnemyConfig()->AbilityDamageRadius[index]);
		bIsActivated = true;
		IntervalTimer = 0;
		return true;
	}
	return false;
}

bool UMSEnemyAbilityProjectile::CheckPrecondition()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return false;
	}
	bool bIsInRange = FVector::Dist(PlayerCharacter->GetActorLocation(), OwnerEnemy->GetActorLocation()) < SearchRange;
	return Super::CheckPrecondition() && bIsInRange;
}
