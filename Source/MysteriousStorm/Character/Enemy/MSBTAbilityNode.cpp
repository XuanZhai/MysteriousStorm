// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBTAbilityNode.h"

#include "AIController.h"
#include "MSEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMSBTAbilityNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int ValidAbilityIndex = BlackboardComp->GetValueAsInt("ValidAbilityIndex");
	if (ValidAbilityIndex == -1)
	{
		return EBTNodeResult::Failed;
	}
	
	if(auto EnemyOwner = Cast<AMSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());EnemyOwner)
	{
		EnemyOwner->GetProcessAbilities()[ValidAbilityIndex]->TryActivateAbility();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
