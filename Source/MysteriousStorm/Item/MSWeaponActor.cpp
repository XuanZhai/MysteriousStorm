// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponActor.h"

AMSWeaponActor::AMSWeaponActor()
{

}

void AMSWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	Offset = FVector(100, 0, 0);
	RuntimeOffset = Offset.RotateAngleAxis(FMath::FRandRange(0.0f, 100.0f), FVector(0, 0, 1));
	RotateSpeed = 200;
	
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

bool AMSWeaponActor::TryReadConfig()
{
	// TODO: 读取武器配置并赋值
	return true;
}

void AMSWeaponActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// 基于上一帧的runtimeoffset,将这一帧的旋转施加到actor上
	
	RuntimeOffset = RuntimeOffset.RotateAngleAxis(RotateSpeed * DeltaSeconds, FVector(0, 0, 1));
	SetActorLocation(OwnerCharacter->GetActorLocation() + RuntimeOffset);
}
