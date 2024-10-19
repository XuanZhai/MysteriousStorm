// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSHUDItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSHUDItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetImage(FSoftObjectPath UIPath);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void SetBackground(int32 Index);

};
