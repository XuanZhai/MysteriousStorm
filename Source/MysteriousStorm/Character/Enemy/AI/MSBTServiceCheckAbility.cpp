// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBTServiceCheckAbility.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MysteriousStorm/Character/MSCharacter.h"


void UMSBTServiceCheckAbility::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AMSEnemyCharacter* EnemyCharacter = Cast<AMSEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	Blackboard->SetValueAsInt("ValidAbilityIndex", -1);
	if (EnemyCharacter)
	{
		for(int i = 0; i < EnemyCharacter->GetProcessAbilities().Num(); i++)
		{
			if(EnemyCharacter->GetProcessAbilities()[i]->IsActivated())
			{
				Blackboard->SetValueAsInt("ValidAbilityIndex", -1);
				return;
			}
		}
		for (int i = 0; i < EnemyCharacter->GetProcessAbilities().Num(); i++)
		{
			if (EnemyCharacter->GetProcessAbilities()[i]->CheckPrecondition())
			{
				Blackboard->SetValueAsInt("ValidAbilityIndex", i);
				break;
			}
		}
	}
}
