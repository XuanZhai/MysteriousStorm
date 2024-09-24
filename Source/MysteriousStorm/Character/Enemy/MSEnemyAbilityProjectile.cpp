// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbilityProjectile.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

bool UMSEnemyAbilityProjectile::TryActivateAbility_Implementation()
{
	if (CheckPrecondition_Implementation())
	{
		auto Projectile = GetWorld()->SpawnActor<AMSEnemyProjectile>(ProjectileClass, OwnerEnemy->GetActorLocation(),
		                                                             OwnerEnemy->GetActorRotation(),
		                                                             FActorSpawnParameters());
		Projectile->InitData(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
		bIsActivated = true;
		IntervalTimer = 0;
		return true;
	}
	return false;
}

bool UMSEnemyAbilityProjectile::CheckPrecondition_Implementation()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return false;
	}
	bool bIsInRange = FVector::Dist(PlayerCharacter->GetActorLocation(), OwnerEnemy->GetActorLocation()) < SearchRange;
	return Super::CheckPrecondition_Implementation() && bIsInRange;
}
