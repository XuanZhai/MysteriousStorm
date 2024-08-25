// Fill out your copyright notice in the Description page of Project Settings.


#include "MSWeaponComponent.h"
#include "GameFramework/Character.h"
#include "MysteriousStorm/Item/MSItemData.h"

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

void UMSWeaponComponent::Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor> WeaponData)
{
	AMSWeaponActor* TestWeapon = GetWorld()->SpawnActor<AMSWeaponActor>(WeaponData);
	TestWeapon->SetOwnerCharacter(Cast<ACharacter>(GetOwner()));
	Weapons.Add(TestWeapon);
}

void UMSWeaponComponent::Internal_RemoveWeapon(AMSWeaponActor* Weapon)
{
}


void UMSWeaponComponent::AddWeapon(UMSItemData* NewWeapon)
{
	// TODO: 类型检查
	Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor>(NewWeapon->AssetBP));
}

void UMSWeaponComponent::RemoveWeapon(UMSItemData* Weapon)
{
	
}

