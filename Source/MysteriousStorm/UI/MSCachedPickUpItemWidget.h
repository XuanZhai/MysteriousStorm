// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSCachedPickUpItemWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSCachedPickUpItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;

public:
	void SetItemName(const FString& NewItemName);

	void SetItemImage(const FSoftObjectPath& UIPath);
};
