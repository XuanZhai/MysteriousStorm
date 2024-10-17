// Fill out your copyright notice in the Description page of Project Settings.


#include "MSEnemyAbilityShell.h"

#include "MysteriousStorm/Character/MSCharacter.h"
#include "MysteriousStorm/Character/Enemy/Projectile/MSEnemyShell.h"

bool UMSEnemyAbilityShell::TryActivateAbility()
{
	if (!CheckPrecondition())return false;
	auto Player = Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto StartAngle = 30;
	// 向周围六个方向发射炮弹
	for (int i = 0; i < 6; i++)
	{
		auto Shell = GetWorld()->SpawnActor<AMSEnemyShell>(ShellClass, OwnerEnemy->GetActorLocation(),
		                                                   FRotator(0, StartAngle, 0), FActorSpawnParameters());
		int index = GetIndex();
		AMSEnemyCharacter* Enemy = Cast<AMSEnemyCharacter>(OwnerEnemy);
		Shell->InitData(
			OwnerEnemy->GetActorLocation() + FRotator(0, StartAngle, 0).RotateVector(FVector::ForwardVector) * 1000,
			Enemy->GetEnemyConfig()->AbilityDamage[index],
			Enemy->GetEnemyConfig()->AbilityDamageRadius[index], Speed);
		StartAngle += 60;
	}
	IntervalTimer = 0;
	return true;
}
