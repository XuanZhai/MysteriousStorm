// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "MSBackpackWidget.generated.h"


/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSBackpackWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:


#pragma region CachedPickUpList

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CachedPickUpItemWidget;

	UPROPERTY(meta = (BindWidget))
	UListView* CachedPickUpListView;

	UFUNCTION(BlueprintCallable)
	void RefreshCachedPickUpListView();
#pragma endregion

};
