// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponActor.h"

#include "MediaPlayer.h"
#include "NiagaraFunctionLibrary.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "MysteriousStorm/Item/Weapon/MSWeaponData.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSEffectConfig.h"
#include "MysteriousStorm/System/MSGameState.h"


UNiagaraComponent* AMSWeaponActor::SpawnNiagaraSystem(FVector Location, FRotator Rotation)
{
	return UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), WeaponNiagaraSystem, Location, Rotation);
}

AMSWeaponActor::AMSWeaponActor()
{
	//TryReadConfig();
	bIsStatic = true;
	bIsEquipped = false;
	StaticMeshComp->SetGenerateOverlapEvents(false);
	CriticalLevel = 0;
	OverloadLevel = 0;
	SetTimeStop(true);
}

void AMSWeaponActor::BeginPlay()
{
	// Level = 1;
	CurrentOffsetInRound = 0;
	Super::BeginPlay();
	if (!bIsEquipped)
	{
		StaticMeshComp->SetGenerateOverlapEvents(true);
	}
	Offset = FVector(-100, 0, 0);
	RuntimeOffset = Offset;
	bIsTimeStopped = false;
	AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
	if (AMSGameState* GameState = GameMode ? GameMode->GetGameState<AMSGameState>() : nullptr; GameState)
	{
		GameState->OnGamePauseUpdated.AddUniqueDynamic(this, &AMSWeaponActor::SetTimeStop);
		Cast<AMSCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetBackpackComponent()
		                                                                     ->OnBackpackOpened.AddUniqueDynamic(
			                                                                     this, &AMSWeaponActor::OnBackpackOpened);
	}
}

void AMSWeaponActor::ApplyEffect(EMSEffect Effect, bool bIsRemove)
{
	float DamageDiff = Cast<UMSWeaponData>(ItemData)->Damage / WeaponConfig.Damage;
	UMSEffectConfig* EffectConfig = GetGameInstance()->GetSubsystem<UMSDataTableSubsystem>()->GetEffectConfig();
	switch (Effect)
	{
	case EMSEffect::SteamStormEffect:
		DamageDiff += bIsRemove ? -EffectConfig->SteamStormHitDamageFactor : EffectConfig->SteamStormHitDamageFactor;
		break;
	default:
		break;
	}
	Cast<UMSWeaponData>(ItemData)->Damage = WeaponConfig.Damage * DamageDiff;
}

int AMSWeaponActor::ProcessEffect()
{
	return 1;
}


// bool AMSWeaponActor::ModifyLevel(bool bIncrease)
// {
// 	if(bIncrease&&Level>=4)
// 	{
// 		return false;
// 	}
// 	if(!bIncrease&&Level<=1)
// 	{
// 		return false;
// 	}
// 	
// 	// 获取当前属性与配置的差值，根据后续effect能够修改的属性增加，这里需要逐条处理
// 	float DamageDiff = Cast<UMSWeaponData>(ItemData)->Damage/WeaponConfig.Damage;
// 		
// 	Level+= bIncrease?1:-1;
// 	InitItemData();
// 		
// 	// 重新应用所有effect
// 	Cast<UMSWeaponData>(ItemData)->Damage = WeaponConfig.Damage * DamageDiff;
// 	return false;
// }

void AMSWeaponActor::OnBackpackOpened()
{
	SetTimeStop(true);
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

void AMSWeaponActor::InitItemData()
{
	UGameInstance* GameInstance = GetGameInstance();

	if (!GameInstance->GetSubsystem<UMSDataTableSubsystem>()->TryGetWeaponConfigByItemID(ItemID, WeaponConfig))
	{
		UE_LOG(LogTemp, Error, TEXT("WeaponConfig is null"));
		return;
	}
	if (ItemData != nullptr)return;
	ItemData = NewObject<UMSWeaponData>();
	FillItemData();

	UMSWeaponData* WeaponData = Cast<UMSWeaponData>(ItemData);
	WeaponData->Damage = WeaponConfig.Damage;
	WeaponData->TriggerTimeInRound = 2;
	WeaponData->TotalRoundTime = 1;
	WeaponType = WeaponConfig.WeaponType;
}

void AMSWeaponActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (OwnerCharacter == nullptr)return;
	// 基于上一帧的runtimeoffset,将这一帧的旋转施加到actor上
	if (bIsStatic && !bIsTimeStopped && OwnerCharacter)
	{
		RuntimeOffset = Offset.RotateAngleAxis(OwnerCharacter->GetActorRotation().Yaw, FVector(0, 0, 1));
		SetActorLocation(OwnerCharacter->GetActorLocation() + RuntimeOffset);
	}
}
