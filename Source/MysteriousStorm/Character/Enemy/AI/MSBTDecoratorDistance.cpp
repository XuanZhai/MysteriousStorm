// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBTDecoratorDistance.h"

#include "AIController.h"

UMSBTDecoratorDistance::UMSBTDecoratorDistance()
{
	MaxDistance = 1000;
}

bool UMSBTDecoratorDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	return PlayerPawn && AIPawn && FVector::Dist(PlayerPawn->GetActorLocation(), AIPawn->GetActorLocation()) < MaxDistance;
}
