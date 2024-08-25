// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSItemWidget.generated.h"

class USizeBox;
class UBorder;
class UImage;
class UMSItemData;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* BGSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BGBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly)
	float TileSize = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	UMSItemData* ItemData;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Size = FVector2D();

protected:
	void SetSize();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UMSItemData*, TargetItemData);
	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	UFUNCTION(BlueprintCallable)
	void CallOnItemRemoved(UMSItemData* TargetItemData);

	void SetTileSize(float NewSize) { TileSize = NewSize; }

	void SetItemData(UMSItemData* NewItemData) { ItemData = NewItemData; }

	UFUNCTION(BlueprintCallable)
	void Refresh();
};
