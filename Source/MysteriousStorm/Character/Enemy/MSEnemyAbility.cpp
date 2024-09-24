// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbility.h"

#include "MysteriousStorm/Character/MSCharacter.h"

bool UMSEnemyAbility::TryActivateAbility_Implementation()
{
	if (Super::TryActivateAbility_Implementation())
	{
		Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetAttributeComponent()->Hurt(OwnerEnemy, Damage);
		return true;
	}
	return false;
}

bool UMSEnemyAbility::CheckPrecondition_Implementation()
{
	return Super::CheckPrecondition_Implementation() && (FVector::Distance(
		GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(), OwnerEnemy->GetActorLocation()) < 100);
}
