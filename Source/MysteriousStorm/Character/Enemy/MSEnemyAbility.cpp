// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbility.h"

#include "MysteriousStorm/Character/MSCharacter.h"

bool UMSEnemyAbility::TryActivateAbility_Implementation()
{
	if (Super::TryActivateAbility_Implementation())
	{
		auto PlayerController = GetWorld()->GetFirstPlayerController();

		if (!PlayerController)
		{
			return false;
		}
		Cast<AMSCharacter>(PlayerController->GetPawn())->GetAttributeComponent()->Hurt(OwnerEnemy, Damage);
		return true;
	}
	return false;
}

bool UMSEnemyAbility::CheckPrecondition_Implementation()
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();

	if (!PlayerController)
	{
		return false;
	}
	return Super::CheckPrecondition_Implementation() && (FVector::Distance(PlayerController->GetPawn()->GetActorLocation(),
	                                                                       OwnerEnemy->GetActorLocation()) < 100);
}
