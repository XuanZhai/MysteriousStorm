// Fill out your copyright notice in the Description page of Project Settings.


#include "MSStorageWidget.h"
#include "MSItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MysteriousStorm/Interactable/MSStorageBox.h"

void UMSStorageWidget::Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent)
{
	TileSize = NewTileSize;
	BackpackComponent = NewBackpackComponent;

	if (!BackpackComponent)
	{
		return;
	}

	ColumnNum = StorageColumnNum;
	RowNum = StorageRowNum;
	Tiles.SetNum(ColumnNum * RowNum);

	if (GridBorder)
	{
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			CanvasPanelSlot->SetSize(FVector2D(TileSize * ColumnNum, TileSize * RowNum));
		}
	}

	CreateLineSegment();
	Refresh();

	BackpackComponent->OnBackpackChanged.AddDynamic(this, &UMSStorageWidget::Refresh);
	BackpackComponent->OnEnterStorageBox.AddDynamic(this, &UMSStorageWidget::UpdateStorageTiles);
}

void UMSStorageWidget::Refresh()
{
	if (!GridPanel || !BackpackComponent)
	{
		return;
	}

	GridPanel->ClearChildren();

	for (const auto& Item : StorageData)
	{
		int32 TileX = 0;
		int32 TileY = 0;
		IndexToTile(Item.Value, TileX, TileY);

		UUserWidget* NewWidget = CreateWidget(this, ItemWidgetClass);

		if (UMSItemWidget* NewItemWidget = NewWidget ? Cast<UMSItemWidget>(NewWidget) : nullptr)
		{
			NewItemWidget->SetTileSize(TileSize);
			NewItemWidget->SetItemData(Item.Key, EGridType::StorageGrid);
			NewItemWidget->OnItemRemoved.AddUniqueDynamic(this, &UMSStorageWidget::OnItemRemoved);
		}

		auto PanelSlot = GridPanel->AddChild(NewWidget);
		if (UCanvasPanelSlot* CanvasPanelSlot = PanelSlot ? Cast<UCanvasPanelSlot>(PanelSlot) : nullptr)
		{
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetPosition(FVector2D(TileX * TileSize, TileY * TileSize));
		}
	}
}

void UMSStorageWidget::ClearStorageTiles()
{
	for (auto& Tile : Tiles)
	{
		Tile.ClearAllData();
	}
}

void UMSStorageWidget::UpdateStorageTiles(AMSStorageBox* StorageBox)
{
	ClearStorageTiles();

	const auto OldStorageData = StorageData;
	StorageData.Empty();

	for (const auto& Item : StorageBox->StorageList)
	{
		if (OldStorageData.Contains(Item) && IsAvailableForNewItem(Item, OldStorageData[Item]))
		{
			AddThisItemAt(Item, OldStorageData[Item]);
		}
		else
		{
			TryAddThisItem(Item);
		}
	}
}


bool  UMSStorageWidget::IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart);

	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	if (TileXStart < 0 || TileYStart < 0) return false;
	if (TileXEnd > ColumnNum || TileYEnd > RowNum) return false;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex);

			if (!Tiles.IsValidIndex(CurrentIndex))
			{
				return false;
			}

			else if (Tiles[CurrentIndex].Item != nullptr || Tiles[CurrentIndex].Bag != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

void UMSStorageWidget::AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	FillTilesWithItem(NewItemData, TopLeftIndex);

	int32 TileX = 0;
	int32 TileY = 0;
	IndexToTile(TopLeftIndex, TileX, TileY);

	StorageData.Add({ NewItemData, TopLeftIndex });
}

void UMSStorageWidget::AddItemBack(UMSItemData* NewItemData)
{
	if (StorageData.Contains(NewItemData))
	{
		AddThisItemAt(NewItemData, StorageData[NewItemData]);
	}
}

void UMSStorageWidget::MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom)  const
{
	bIsRight = ((int)MousePosition.X % (int)TileSize) > ((int)TileSize / 2);
	bIsBottom = ((int)MousePosition.Y % (int)TileSize) > ((int)TileSize / 2);
}

void UMSStorageWidget::OnItemRemoved(UMSItemData* TargetItemData)
{
	for (auto& Tile : Tiles)
	{
		if (Tile.Item == TargetItemData)
		{
			Tile.ClearItemData();
		}
		else if (Tile.Bag == TargetItemData)
		{
			Tile.ClearAllData();
		}
	}

	BackpackComponent->InteractingStorageBox->StorageList.Remove(TargetItemData);
	UpdateStorageTiles(BackpackComponent->InteractingStorageBox);
}

bool UMSStorageWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UMSItemData* NewItemData = GetItemDataFromDragDropOperation(InOperation);
	EGridType DragSource = GetDragSourceFromDragDropOperation(InOperation);

	bool bFindPlaceToDrop = false;

	if (IsItemAvailableToPut(NewItemData))
	{
		AddThisItemAt(NewItemData, DropItemTopLeftTile);
		bFindPlaceToDrop = true;
	}
	else
	{
		bFindPlaceToDrop = TryAddThisItem(NewItemData);
	}

	if (bFindPlaceToDrop)
	{
		if (DragSource == BackpackGrid || DragSource == EGridType::StorageGrid)
		{
			BackpackComponent->InteractingStorageBox->StorageList.Add(NewItemData);
			UpdateStorageTiles(BackpackComponent->InteractingStorageBox);
			Refresh();
		}
	}

	if (OnMouseDropped.IsBound())
	{
		OnMouseDropped.Broadcast();
	}

	return true;
}

bool UMSStorageWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto ScreenSpacePosition = InDragDropEvent.GetScreenSpacePosition();
	auto LocalScreenSpacePosition = InGeometry.AbsoluteToLocal(ScreenSpacePosition);

	bool bIsRight = false;
	bool bIsBottom = false;
	MousePositionInTile(LocalScreenSpacePosition, bIsRight, bIsBottom);

	UMSItemData* Payload = GetItemDataFromDragDropOperation(InOperation);

	if (!Payload)
	{
		return false;
	}

	int32 XPos = Payload->XUISize - (bIsRight ? 1 : 0);
	int32 YPos = Payload->YUISize - (bIsBottom ? 1 : 0);

	XPos = FMath::Clamp(XPos, 0, XPos);
	YPos = FMath::Clamp(YPos, 0, YPos);

	int32 XMousePosToTile = (int)(LocalScreenSpacePosition.X / TileSize);
	int32 YMousePosToTile = (int)(LocalScreenSpacePosition.Y / TileSize);

	XMousePosToTile -= (XPos / 2);
	YMousePosToTile -= (YPos / 2);

	XMousePosToTile = FMath::Clamp(XMousePosToTile, 0, ColumnNum);
	YMousePosToTile = FMath::Clamp(YMousePosToTile, 0, RowNum);

	TileToIndex(XMousePosToTile, YMousePosToTile, DropItemTopLeftTile);

	return true;
}