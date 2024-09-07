// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponComponent.h"

#include "Core/Tests/Containers/TestUtils.h"
#include "GameFramework/Character.h"
#include "MysteriousStorm/Item/MSItemData.h"

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
	for (const auto WeaponData : TestWeaponData)
	{
		Internal_CreateNewWeapon(WeaponData);
	}
}

#pragma endregion

#pragma region internal

void UMSWeaponComponent::Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor> WeaponData)
{
	AMSWeaponActor* Weapon = GetWorld()->SpawnActor<AMSWeaponActor>(WeaponData);
	Weapon->SetOwnerCharacter(Cast<ACharacter>(GetOwner()));
	Weapon->bIsStatic = false;
	Weapons.Add(Weapon);

	
	AMSWeaponActor* StaticWeapon = GetWorld()->SpawnActor<AMSWeaponActor>(WeaponData);
	StaticWeapon->SetOwnerCharacter(Cast<ACharacter>(GetOwner()));
	StaticWeapon->bIsStatic = true;
	StaticWeapons.Add(StaticWeapon);
}

void UMSWeaponComponent::Internal_RemoveWeapon(UMSItemData* Weapon)
{
	for (const auto WeaponActor : Weapons)
	{
		if (WeaponActor->GetItemData() == Weapon)
		{
			Weapons.Remove(WeaponActor);
			WeaponActor->Destroy();
			break;
		}
	}
	for (const auto WeaponActor : StaticWeapons)
	{
		if (WeaponActor->GetItemData() == Weapon)
		{
			Weapons.Remove(WeaponActor);
			WeaponActor->Destroy();
			break;
		}
	}
}

#pragma endregion

#pragma region publicInterface


void UMSWeaponComponent::AddWeapon(UMSItemData* NewWeapon)
{
	// TODO: 类型检查
	for (auto WeaponEntity : Weapons)
	{
		if(WeaponEntity->ItemData->ID==NewWeapon->ID)
		{
			// 如果已经拥有了同种类的武器，则先更改等级读取新配置，保留原有buff，再施加新武器buff
			if(!WeaponEntity->ModifyLevel(true))
			{
				UE_LOG(LogTemp, Error, TEXT("can not remove weapon because of level"));
				return;
			}
			// 应用新武器上挂载的effect
			for(auto NewEffect: NewWeapon->Effects)
			{
				WeaponEntity->ApplyEffect(NewEffect);
			}
		}
	}
	Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor>(NewWeapon->AssetBP));
}

void UMSWeaponComponent::RemoveWeapon(UMSItemData* Weapon)
{
	for (auto WeaponEntity : Weapons)
	{
		if(WeaponEntity->ItemData->ID==Weapon->ID)
		{
			// 逻辑与加武器一样
			if(!WeaponEntity->ModifyLevel(false))
			{
				UE_LOG(LogTemp, Error, TEXT("can not remove weapon because of level"));
				return;
			}
			// 通过除去武器上挂载的effect计算新的数值
			for(auto TargetEffect: Weapon->Effects)
			{
				WeaponEntity->ApplyEffect(TargetEffect,true);
			}
		}
	}
	Internal_RemoveWeapon(Weapon);
}

void UMSWeaponComponent::InitialWeaponSystem()
{
	// 每局开始时从背包中加载武器
}
# pragma endregion
