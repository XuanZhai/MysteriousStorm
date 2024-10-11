// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSStarWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSStarWidget : public UUserWidget
{
	GENERATED_BODY()
	

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))


public:
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchImage(int32 Index);

	UFUNCTION(BlueprintImplementableEvent)
	void SetSize(FVector2D NewSize);
};
