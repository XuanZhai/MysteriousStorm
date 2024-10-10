// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSGridWidget.h"
#include "MSItemWidget.generated.h"

class UCanvasPanel;
class USizeBox;
class UBorder;
class UImage;
class UMSItemData;
class UMSTipsWidget;

UCLASS(BlueprintType)
class MYSTERIOUSSTORM_API UMSDragPayload : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	UMSItemData* ItemData;

	EGridType DragSource;

	UMSDragPayload()
	{
		ItemData = nullptr;
		DragSource = EGridType::CachedGrid;
	}

	UMSDragPayload(UMSItemData* NewData, EGridType NewSource)
	{
		ItemData = NewData;
		DragSource = NewSource;
	}
};

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	USizeBox* BGSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BGBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMSTipsWidget* WB_TipsWidget;

	UPROPERTY(BlueprintReadOnly)
	float TileSize = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	UMSDragPayload* ItemPayload;

	UPROPERTY(BlueprintReadWrite)
	FVector2D Size = FVector2D();

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* UIMaterial;

protected:
	void SetSize();

	void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UMSItemData*, TargetItemData);
	UPROPERTY(BlueprintAssignable)
	FOnItemRemoved OnItemRemoved;

	UFUNCTION(BlueprintCallable)
	void CallOnItemRemoved();

	void SetTileSize(float NewSize) { TileSize = NewSize; }

	void SetItemData(UMSItemData* NewItemData, EGridType NewItemSource);

	UMSItemData* GetItemData() const { return ItemPayload ? ItemPayload->ItemData : nullptr;  }

	UFUNCTION(BlueprintCallable)
	void Refresh();

	UMSDragPayload* GetDragPayload() const {return ItemPayload; }

	UFUNCTION(BlueprintCallable)
	void RotateUI();

	UFUNCTION(BlueprintCallable)
	void UseItem();
};
