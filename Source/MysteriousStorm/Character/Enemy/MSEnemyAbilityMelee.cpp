// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbilityMelee.h"

#include "MysteriousStorm/Character/MSCharacter.h"

bool UMSEnemyAbilityMelee::TryActivateAbility()
{
	if (Super::TryActivateAbility())
	{
		auto Player = Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (!Player)
		{
			return false;
		}
		
		AMSEnemyCharacter* EnemyPlayer = Cast<AMSEnemyCharacter>(OwnerEnemy);
		Player->GetAttributeComponent()->Hurt(OwnerEnemy, EnemyPlayer->GetEnemyConfig()->AbilityDamage[GetIndex()]);
		return true;
	}
	return false;
}

bool UMSEnemyAbilityMelee::CheckPrecondition()
{
	auto Player = Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!Player)
	{
		return false;
	}
	return Super::CheckPrecondition() && (FVector::Distance(Player->GetActorLocation(),
	                                                                       OwnerEnemy->GetActorLocation()) < 100);
}


