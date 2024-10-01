// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateHealthBar(float HealthPercent);

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float healthPercent;
};
