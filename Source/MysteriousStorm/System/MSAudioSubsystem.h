// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MSAudioTableRow.h"
#include "MSAudioSubsystem.generated.h"

/**
 * 
 */
UCLASS()

class MYSTERIOUSSTORM_API UMSAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void PlayAudioAt(int32 ItemID, EAudioType AudioType, FVector Location);
	
	UFUNCTION(BlueprintCallable)
	void Play2DAudio(int32 ItemID,EAudioType AudioType);

	const static int UIItemID = -1;
};
