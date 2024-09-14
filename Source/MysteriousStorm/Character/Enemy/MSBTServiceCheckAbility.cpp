// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBTServiceCheckAbility.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MysteriousStorm/Character/MSCharacter.h"

void UMSBTServiceCheckAbility::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
	AMSEnemyCharacter* EnemyCharacter = Cast<AMSEnemyCharacter>(SearchData.OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* Blackboard = SearchData.OwnerComp.GetBlackboardComponent();
	Blackboard->SetValueAsInt("ValidAbilityIndex", -1);
	if (EnemyCharacter)
	{
		for (int i = 0; i < EnemyCharacter->GetProcessAbilities().Num(); i++)
		{
			if (EnemyCharacter->GetProcessAbilities()[i]->CheckPrecondition())
			{
				Blackboard->SetValueAsInt("ValidAbilityIndex", i);
				break;
			}
		}
	}
	Blackboard->SetValueAsInt("ValidAbilityIndex", -1);
}
