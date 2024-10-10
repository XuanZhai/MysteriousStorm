// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSGridWidget.h"
#include "MSBackpackGridWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UMSItemWidget;
class UMSItemData;
class UMSBackpackComponent;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSBackpackGridWidget : public UMSGridWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* GridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BagTime = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemTime = 0.2f;

public:
	UFUNCTION(BlueprintCallable)
	void Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent);

	UFUNCTION(BlueprintCallable)
	void Refresh();

#pragma region Backpack

	virtual bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const override;

	virtual void AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex) override;

	UFUNCTION(BlueprintCallable)
	void AddItemBack(UMSItemData* NewItemData);

	void RetrieveContainedBackpacks(UMSItemData* TargetItemData, int32 TopLeftIndex, TSet<UMSItemData*>& OutBackpacks);

	void RetrieveItemsFromBackpack(UMSItemData* TargetBagData, int32 TopLeftIndex, TSet<UMSItemData*>& OutItems);

	UFUNCTION()
	void CalculateGridData();

	void FillVisitedList(UMSItemData* ItemData, TArray<bool>& VisitedList, int32 TopLeftIndex) const;

	void ApplySpecialItemEffect(UMSItemData* ItemData, int32 Index);
#pragma endregion

#pragma region UI
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateLineSegment();

	UFUNCTION(BlueprintCallable)
	void OnItemRemoved(UMSItemData* TargetItemData);

	UFUNCTION(BlueprintCallable)
	void MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom) const;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);
#pragma endregion
};
