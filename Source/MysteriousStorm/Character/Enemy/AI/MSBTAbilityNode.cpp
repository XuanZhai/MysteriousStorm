// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBTAbilityNode.h"

#include "AIController.h"
#include "MysteriousStorm/Character/Enemy/MSEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UMSBTAbilityNode::UMSBTAbilityNode()
{
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UMSBTAbilityNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UMSBTAbilityNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int ValidAbilityIndex = BlackboardComp->GetValueAsInt("ValidAbilityIndex");
	if (ValidAbilityIndex == -1)
	{
		return ;
	}
	
	if(auto EnemyOwner = Cast<AMSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());EnemyOwner)
	{	
		if (ValidAbilityIndex < EnemyOwner->GetProcessAbilities().Num())
		{
			EnemyOwner->GetProcessAbilities()[ValidAbilityIndex]->TryActivateAbility();
		}
	}
}
