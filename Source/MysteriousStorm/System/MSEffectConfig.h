// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MSEffectConfig.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSEffectConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UMSEffectConfig();

	UPROPERTY(EditDefaultsOnly, Category = "Storm|SteamStorm")
	float SteamStormSelfDamageFactor;

	UPROPERTY(EditDefaultsOnly, Category = "Storm|SteamStorm")
	float SteamStormHitDamageFactor;

	UPROPERTY(EditDefaultsOnly, Category = "Jewelry|Critical")
	int CriticalDeltaDamage;
};
