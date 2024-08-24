// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

public:
	TWeakObjectPtr<UListView> ParentListView;

};
