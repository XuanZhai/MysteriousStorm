// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MysteriousStorm/Item/MSWeaponActor.h"
#include "MSWeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERIOUSSTORM_API UMSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMSWeaponComponent();

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapons")
	TArray<AMSWeaponActor*> Weapons;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapons")
	TArray<TSubclassOf<AMSWeaponActor>> TestWeaponData;
	
	// Called when the game starts
	virtual void BeginPlay() override;
	void Internal_CreateNewWeapon(TSubclassOf<AMSWeaponActor> WeaponData);
	void Internal_RemoveWeapon(AMSWeaponActor* Weapon);

public:	

	virtual void AddWeapon(UMSItemData* NewWeapon);
	virtual void RemoveWeapon(UMSItemData* Weapon);
		
};
