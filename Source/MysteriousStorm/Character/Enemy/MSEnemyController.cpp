// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyController.h"

#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "MysteriousStorm/System/MSGameState.h"

void AMSEnemyController::SetEnableAI(bool bEnable)
{
	bIsEnableAI = bEnable;
}

void AMSEnemyController::OnBackpackOpened()
{
	SetEnableAI(false);
}

void AMSEnemyController::OnBackpackClosed()
{
	SetEnableAI(true);
}

void AMSEnemyController::BeginPlay()
{
	Super::BeginPlay();
	bIsEnableAI = true;
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (AMSGameState* GameState = GameMode ? GameMode->GetGameState<AMSGameState>() : nullptr; GameState)
	{
		GameState->OnGamePauseUpdated.AddUniqueDynamic(this, &AMSEnemyController::SetEnableAI);
		UMSBackpackComponent* BackpackComponent =
			Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetBackpackComponent();
		BackpackComponent->OnBackpackOpened.AddUniqueDynamic(this, &AMSEnemyController::OnBackpackOpened);
		BackpackComponent->OnBackpackClosed.AddUniqueDynamic(this, &AMSEnemyController::OnBackpackClosed);
	}
}
