// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSGridWidget.h"
#include "MSItemWidget.generated.h"

class USizeBox;
class UBorder;
class UImage;
class UMSItemData;

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
	USizeBox* BGSizeBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* BGBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* ItemImage;

	UPROPERTY(BlueprintReadOnly)
	float TileSize = 0.0f;

	//UPROPERTY(BlueprintReadOnly)
	//UMSItemData* ItemData;

	UPROPERTY(BlueprintReadOnly)
	UMSDragPayload* ItemPayload;

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

	void SetItemData(UMSItemData* NewItemData, EGridType NewItemSource);

	UFUNCTION(BlueprintCallable)
	void Refresh();

	UMSDragPayload* GetDragPayload() const {return ItemPayload; }
};
