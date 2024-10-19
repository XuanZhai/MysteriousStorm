// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponComponent.h"

#include "MSBackpackComponent.h"
#include "Core/Tests/Containers/TestUtils.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Item/Weapon/MSIntermittentWeapon.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"

#pragma region lifetime
// Sets default values for this component's properties
UMSWeaponComponent::UMSWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMSWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	auto BackpackComponent = Cast<UMSBackpackComponent>(
		GetOwner()->GetComponentByClass(UMSBackpackComponent::StaticClass()));
	BackpackComponent->OnBackpackClosed.AddDynamic(this, &UMSWeaponComponent::ResetCycle);
	auto TotalTime = 2 * TestWeaponData.Num();
	auto CurrentTime = 0;
	// TODO: 初始化逻辑
	for (const auto WeaponClass : TestWeaponData)
	{
		UMSWeaponData* WeaponData = NewObject<UMSWeaponData>();
		WeaponData->TotalRoundTime = TotalTime;
		WeaponData->TriggerTimeInRound = CurrentTime;
		WeaponData->Damage = 10;
		Internal_CreateNewWeapon(WeaponClass, WeaponData);
		CurrentTime++;
	}
	ResetCycle();
}

#pragma endregion

#pragma region internal

void UMSWeaponComponent::Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor> WeaponClass, UMSWeaponData* WeaponData)
{
	// AMSWeaponActor* Weapon = GetWorld()->SpawnActor<AMSWeaponActor>(WeaponClass);
	AMSWeaponActor* Weapon = Cast<AMSWeaponActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, WeaponClass, GetOwner()->GetTransform()));
	Weapon->bIsEquipped = true;
	Weapon->ItemData = WeaponData;
	Weapon->SetOwnerCharacter(Cast<ACharacter>(GetOwner()));
	Weapon->bIsStatic = false;
	Weapon->FinishSpawning(GetOwner()->GetTransform());
	Weapon->GetFakeComponent()->SetVisibility(false);
	Weapons.Add(Weapon);


	// AMSWeaponActor* StaticWeapon = GetWorld()->SpawnActor<AMSWeaponActor>(WeaponClass);
	AMSWeaponActor* StaticWeapon = Cast<AMSWeaponActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, WeaponClass, GetOwner()->GetTransform()));
	StaticWeapon->SetOwnerCharacter(Cast<ACharacter>(GetOwner()));
	StaticWeapon->bIsEquipped = true;
	StaticWeapon->ItemData = WeaponData;
	StaticWeapon->bIsStatic = true;
	StaticWeapon->FinishSpawning(GetOwner()->GetTransform());
	StaticWeapon->GetFakeComponent()->SetVisibility(false);
	StaticWeapons.Add(StaticWeapon);
}

void UMSWeaponComponent::Internal_RemoveWeapon(UMSItemData* WeaponData)
{
	for (const auto WeaponActor : Weapons)
	{
		if (WeaponActor->GetItemData() == WeaponData)
		{
			Weapons.Remove(WeaponActor);
			WeaponActor->Destroy();
			break;
		}
	}
	for (const auto WeaponActor : StaticWeapons)
	{
		if (WeaponActor->GetItemData() == WeaponData)
		{
			StaticWeapons.Remove(WeaponActor);
			WeaponActor->Destroy();
			break;
		}
	}
}

#pragma endregion

#pragma region publicInterface

void UMSWeaponComponent::ResetCycle()
{
	for (auto Weapon : Weapons)
	{
		Weapon->SetTimeStop(false);
		if(auto IntermittentWeapon = Cast<AMSIntermittentWeapon>(Weapon);IntermittentWeapon)
		{
			IntermittentWeapon->ResetWeapon();
		}
	}
	for (auto Weapon : StaticWeapons)
	{
		Weapon->SetTimeStop(false);
		if(auto IntermittentWeapon = Cast<AMSIntermittentWeapon>(Weapon);IntermittentWeapon)
		{
			IntermittentWeapon->ResetWeapon();
		}
	}
}

void UMSWeaponComponent::AddWeapon(UMSItemData* NewWeapon)
{
	// TODO: 类型检查
	// for (auto WeaponEntity : Weapons)
	// {
	// 	if (WeaponEntity->ItemData->ID == NewWeapon->ID)
	// 	{
	// 		// 如果已经拥有了同种类的武器，则先更改等级读取新配置，保留原有buff，再施加新武器buff
	// 		if (!WeaponEntity->ModifyLevel(true))
	// 		{
	// 			UE_LOG(LogTemp, Error, TEXT("can not remove weapon because of level"));
	// 			return;
	// 		}
	// 		// 应用新武器上挂载的effect
	// 		for (auto NewEffect : NewWeapon->Effects)
	// 		{
	// 			WeaponEntity->ApplyEffect(NewEffect);
	// 		}
	// 	}
	// }
	Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor>(NewWeapon->AssetBP), Cast<UMSWeaponData>(NewWeapon));
}

void UMSWeaponComponent::RemoveWeapon(UMSItemData* Weapon)
{
	// for (auto WeaponEntity : Weapons)
	// {
	// 	if (WeaponEntity->ItemData->ID == Weapon->ID)
	// 	{
	// 		// 逻辑与加武器一样
	// 		if (!WeaponEntity->ModifyLevel(false))
	// 		{
	// 			UE_LOG(LogTemp, Error, TEXT("can not remove weapon because of level"));
	// 			return;
	// 		}
	// 		// 通过除去武器上挂载的effect计算新的数值
	// 		for (auto TargetEffect : Weapon->Effects)
	// 		{
	// 			WeaponEntity->ApplyEffect(TargetEffect, true);
	// 		}
	// 	}
	// }
	Internal_RemoveWeapon(Weapon);
}

void UMSWeaponComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMSWeaponComponent::InitialWeaponSystem()
{
	// 每局开始时从背包中加载武器
}
# pragma endregion
