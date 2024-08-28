// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSGridWidget.h"
#include "MSCachedGridWidget.generated.h"

class UMSBackpackWidget;
class UCanvasPanel;
class UBorder;
class UMSItemWidget;
class UMSItemData;
class UMSBackpackComponent;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSCachedGridWidget : public UMSGridWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* GridPanel;

	UPROPERTY(BlueprintReadWrite)
	UMSBackpackComponent* BackpackComponent;

	UPROPERTY(BlueprintReadWrite)
	float TileSize = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMSItemWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DropItemTopLeftTile = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDropLocation = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <UMSItemData*> CachedTiles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ColumnNum = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RowNum = 0;

public:
	UFUNCTION(BlueprintCallable)
	void Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent);

	UFUNCTION(BlueprintCallable)
	void Refresh();

#pragma region Backpack
	
	void ClearCachedTiles();

	UFUNCTION(BlueprintCallable)
	void UpdateCachedTiles();

	UFUNCTION(BlueprintCallable)
	void AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex);

	bool TryAddThisItem(UMSItemData* NewItemData);

#pragma region

#pragma region UI
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateLineSegment();

	UFUNCTION(BlueprintCallable)
	bool IsItemAvailableToPut(UMSItemData* TargetItem) const;

	UFUNCTION(BlueprintCallable)
	void OnItemRemoved(UMSItemData* TargetItemData);

	UFUNCTION(BlueprintCallable)
	void MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom) const;

	UFUNCTION(BlueprintCallable)
	UMSItemData* GetItemDataFromDragDropOperation(UDragDropOperation* InOperation) const;

	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );

	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );
#pragma endregion

};
