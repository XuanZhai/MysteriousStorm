// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSGridWidget.generated.h"

class UMSItemData;
class UMSItemWidget;
class UMSBackpackComponent;

UENUM(BlueprintType)
enum EGridType : uint8
{
	CachedGrid = 0 UMETA(DisplayName = "CachedGrid"),
	BackpackGrid = 1 UMETA(DisplayName = "BackpackGrid"),
	DEFAULT UMETA(DisplayName = "Default"),
};

USTRUCT(BlueprintType)
struct FTileinfo
{
	GENERATED_BODY()

	UMSItemData* Item;
	UMSItemData* Bag;
	bool bHasBag;
	bool bHasItem;

	FTileinfo()
	{
		ClearAllData();
	}

	void ClearAllData()
	{
		Item = nullptr;
		Bag = nullptr;
		bHasBag = false;
		bHasItem = false;
	}
	void ClearItemData()
	{
		Item = nullptr;
		bHasItem = false;
	}
	bool HasBag() const { return bHasBag; }
	bool HasItem() const { return bHasBag && bHasItem; }
	void SetBag(UMSItemData* NewBag) { Bag = NewBag; bHasBag = true; }
	void SetItem(UMSItemData* NewItem) { Item = NewItem; bHasItem = true; }
};

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
 	UPROPERTY(BlueprintReadWrite)
 	UMSBackpackComponent* BackpackComponent;

	UPROPERTY(BlueprintReadWrite)
	float TileSize = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMSItemWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <FTileinfo> Tiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ColumnNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RowNum = 0;

public:
	UPROPERTY(BlueprintReadWrite)
	int32 DropItemTopLeftTile = 0;

	UPROPERTY(BlueprintReadWrite)
	bool bDrawDropLocation = false;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMouseDropped);
	UPROPERTY(BlueprintAssignable)
	FOnMouseDropped OnMouseDropped;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNeedDropBack, UMSItemData*, BackItemData);
	UPROPERTY(BlueprintAssignable)
	FNeedDropBack NeedDropBack;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPutChildToGround, UMSItemData*, BackItemData);
	UPROPERTY(BlueprintAssignable)
	FPutChildToGround PutChildToGround;

protected:

	UFUNCTION(BlueprintCallable)
	void IndexToTile(const int32 InIndex, int32& OutX, int32& OutY) const;

	UFUNCTION(BlueprintCallable)
	void TileToIndex(const int32 InX, const int32 InY, int32& OutIndex) const;

	UFUNCTION(BlueprintCallable)
	virtual bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const { return false; };

	UFUNCTION(BlueprintCallable)
	bool IsItemAvailableToPut(UMSItemData* TargetItem) const;

	void FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex);

	UFUNCTION(BlueprintCallable)
	virtual void AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex) {};

	UFUNCTION(BlueprintCallable)
	UMSItemData* GetItemDataFromDragDropOperation(UDragDropOperation* InOperation) const;

	UFUNCTION(BlueprintCallable)
	EGridType GetDragSourceFromDragDropOperation(UDragDropOperation* InOperation) const;

	UFUNCTION(BlueprintCallable)
	UMSItemWidget* GetItemWidgetFromDragDropOperation(UDragDropOperation* InOperation) const;

public:
	UFUNCTION()
	bool TryAddThisItem(UMSItemData* NewItemData);
};
