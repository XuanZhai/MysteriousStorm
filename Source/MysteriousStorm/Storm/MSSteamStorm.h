// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSStormBase.h"
#include "MSSteamStorm.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSSteamStorm : public AMSStormBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Steam")
	float SteamSelfDamageFactor;

	UPROPERTY(EditDefaultsOnly, Category = "Steam")
	float SteamHitDamageFactor;

public:
	AMSSteamStorm();
};
