// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSTipsWidget.generated.h"

class UTextBlock;
struct FTimerHandle;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSTipsWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* TXT_Block;

	FString TextInfo;

	FTimerHandle DelayHandle;

	bool bIsVisible = false;

protected:
	void ShowTipsInternal();

public:
	void ShowTips(FString Info);

	void HideTips();
};
