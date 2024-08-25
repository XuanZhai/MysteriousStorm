// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemActor.h"
#include "GameFramework/Character.h"
#include "MSWeaponActor.generated.h"

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None,
	Sword,
	Hammer,
	Grenade,
	Dart,
	MachineGun,
	ShotGun,
};

/**
 * 
 */
UCLASS(Abstract)
class MYSTERIOUSSTORM_API AMSWeaponActor : public AMSItemActor
{
	GENERATED_BODY()
protected:
	
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY(EditAnywhere, Category="WeaponParameter")
	EWeaponType WeaponType;

	FVector RuntimeOffset;
	FVector Offset;
	float RotateSpeed;

public:
	AMSWeaponActor();

	void SetOwnerCharacter(ACharacter* NewOwnerCharacter);
	virtual void BeginPlay() override;
	virtual bool TryAttack();
	virtual bool TryReadConfig();
	virtual void Tick(float DeltaSeconds) override;
	
};
