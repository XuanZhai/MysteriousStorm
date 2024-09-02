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

public:
	UFUNCTION(BlueprintCallable)
	void Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent);

	UFUNCTION(BlueprintCallable)
	void Refresh();

#pragma region Backpack
	
	void ClearCachedTiles();

	UFUNCTION(BlueprintCallable)
	void UpdateCachedTiles();

	virtual bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const override;

	virtual void AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex) override;

	UFUNCTION(BlueprintCallable)
	void AddItemBack(UMSItemData* NewItemData);

	UFUNCTION(BlueprintCallable)
	void AddChildItem(UMSItemData* NewItemData);


#pragma region

#pragma region UI
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateLineSegment();

	UFUNCTION(BlueprintCallable)
	void OnItemRemoved(UMSItemData* TargetItemData);

	UFUNCTION(BlueprintCallable)
	void MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom) const;

	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );

	virtual bool NativeOnDragOver( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );
#pragma endregion

};
