// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSGridWidget.h"
#include "MSStorageWidget.generated.h"

class UMSBackpackWidget;
class UCanvasPanel;
class UBorder;
class UMSItemWidget;
class UMSItemData;
class UMSBackpackComponent;
class AMSStorageBox;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSStorageWidget : public UMSGridWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* GridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 StorageColumnNum = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 StorageRowNum = 10;

	TMap<UMSItemData*, int32> StorageData;

protected:
	virtual bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const override;

	virtual void AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex) override;

	UFUNCTION(BlueprintCallable)
	void OnItemRemoved(UMSItemData* TargetItemData);

	UFUNCTION(BlueprintCallable)
	void MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom) const;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

public:
	UFUNCTION(BlueprintCallable)
	void Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent);

	UFUNCTION(BlueprintCallable)
	void Refresh();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateLineSegment();

	void ClearStorageTiles();

	UFUNCTION(BlueprintCallable)
	void UpdateStorageTiles(AMSStorageBox* StorageItemList);

	UFUNCTION(BlueprintCallable)
	void AddItemBack(UMSItemData* NewItemData);
};
