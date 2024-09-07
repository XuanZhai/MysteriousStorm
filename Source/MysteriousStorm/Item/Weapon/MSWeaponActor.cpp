// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponActor.h"

#include "MysteriousStorm/System/MSDataTableSubsystem.h"


AMSWeaponActor::AMSWeaponActor()
{
	//TryReadConfig();
	bIsStatic = true;
}

void AMSWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	TryReadConfig();

	Offset = FVector(-100, 0, 0);
	RuntimeOffset = Offset;
	bIsTimeStopped = false;
}


void AMSWeaponActor::SetTimeStop(bool bIsTimeStop)
{
	bIsTimeStopped = bIsTimeStop;
}

void AMSWeaponActor::SetOwnerCharacter(ACharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;
	SetActorLocation(OwnerCharacter->GetActorLocation() + Offset);
}

bool AMSWeaponActor::TryAttack()
{
	return true;
}

void AMSWeaponActor::ApplyDamage()
{
}

void AMSWeaponActor::SearchEnemy()
{
}

bool AMSWeaponActor::TryReadConfig()
{
	UGameInstance* GameInstance = GetGameInstance();
	GameInstance->GetSubsystem<UMSDataTableSubsystem>()->TryGetWeaponConfigByItemID(ItemID, WeaponConfig);
	return true;
}

void AMSWeaponActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// 基于上一帧的runtimeoffset,将这一帧的旋转施加到actor上
	if (bIsStatic && !bIsTimeStopped)
	{
		RuntimeOffset = Offset.RotateAngleAxis(OwnerCharacter->GetActorRotation().Yaw, FVector(0, 0, 1));
		SetActorLocation(OwnerCharacter->GetActorLocation() + RuntimeOffset);
	}
	
}
