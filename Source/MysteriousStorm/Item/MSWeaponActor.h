// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSItemActor.h"
#include "MSWeaponActor.generated.h"

UENUM(BlueprintType)
enum EWeaponType : uint8
{
	Sword = 0
};

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSWeaponActor : public AMSItemActor
{
	GENERATED_BODY()
	
};
