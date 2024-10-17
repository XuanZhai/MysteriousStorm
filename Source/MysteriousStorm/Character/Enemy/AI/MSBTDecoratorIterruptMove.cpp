// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBTDecoratorIterruptMove.h"

#include "AIController.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyCharacter.h"

bool UMSBTDecoratorIterruptMove::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AMSEnemyCharacter* Enemy = Cast<AMSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	for (auto Ability : Enemy->GetAbilities())
	{
		if(Ability->IsActivated()&&Ability->bInterruptMovement)
		{
			return false;
		}
	}
	return true;
}
