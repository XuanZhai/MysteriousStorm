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
	Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor>(NewWeapon->AssetBP));
}

void UMSWeaponComponent::RemoveWeapon(UMSItemData* Weapon)
{
	Internal_RemoveWeapon(Weapon);
}
# pragma endregion
