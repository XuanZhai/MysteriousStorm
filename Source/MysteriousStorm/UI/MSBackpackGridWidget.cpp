// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackGridWidget.h"
#include "MSItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MysteriousStorm/UI/MSBackpackWidget.h"

void UMSBackpackGridWidget::Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent)
{
	TileSize = NewTileSize;
	BackpackComponent = NewBackpackComponent; 

	if (!BackpackComponent)
	{
		return;
	}

	ColumnNum = BackpackComponent->ColumnNumber;
	RowNum = BackpackComponent->RowNumber;
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

	BackpackComponent->OnBackpackChanged.AddDynamic(this, &UMSBackpackGridWidget::Refresh);
}

void UMSBackpackGridWidget::Refresh()
{
	if (!GridPanel || !BackpackComponent)
	{
		return;
	}

	GridPanel->ClearChildren();

	const TMap<UMSItemData*, int32>& NewItems = BackpackComponent->GetItems();
	for (const auto& Item : NewItems)
	{
		int32 TileX = 0;
		int32 TileY = 0;
		IndexToTile(Item.Value, TileX, TileY);

		UUserWidget* NewWidget = CreateWidget(this, ItemWidgetClass);

		if (UMSItemWidget* NewItemWidget = NewWidget ? Cast<UMSItemWidget>(NewWidget) : nullptr)
		{
			NewItemWidget->SetTileSize(TileSize);
			NewItemWidget->SetItemData(Item.Key,EGridType::BackpackGrid);
			NewItemWidget->OnItemRemoved.AddUniqueDynamic(this, &UMSBackpackGridWidget::OnItemRemoved);
		}

		auto PanelSlot = GridPanel->AddChild(NewWidget);
		if (UCanvasPanelSlot* CanvasPanelSlot = PanelSlot ? Cast<UCanvasPanelSlot>(PanelSlot) : nullptr)
		{
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetPosition(FVector2D(TileX * TileSize, TileY * TileSize));
		}
	}
}

void UMSBackpackGridWidget::OnItemRemoved(UMSItemData* TargetItemData)
{
	for (auto& Tile : Tiles)
	{
		if (Tile.Item == TargetItemData)
		{
			Tile.ClearItemData();
		}
		else if (Tile.Bag == TargetItemData)
		{
			if (Tile.bHasItem)
			{
				if (PutChildToGround.IsBound())
				{
					PutChildToGround.Broadcast(Tile.Item);
				}
				BackpackComponent->RemoveItem(Tile.Item);
			} 
			BackpackComponent->RemoveItem(Tile.Bag,false);
			Tile.ClearAllData();
		}
	}
}

void UMSBackpackGridWidget::MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom)  const
{
	bIsRight = ((int)MousePosition.X % (int)TileSize) > ((int)TileSize / 2);
	bIsBottom = ((int)MousePosition.Y % (int)TileSize) > ((int)TileSize / 2);
}

bool UMSBackpackGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
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
		if (DragSource == EGridType::CachedGrid)
		{
			if (NeedDropBack.IsBound())
			{
				NeedDropBack.Broadcast(NewItemData);
			}
		}
		else
		{
			bFindPlaceToDrop = TryAddThisItem(NewItemData);
		}
	}

	if (OnMouseDropped.IsBound())
	{
		OnMouseDropped.Broadcast();
	}

	return true;
}

bool UMSBackpackGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
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

bool UMSBackpackGridWidget::IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const
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

			if (NewItemData->IsBag() && Tiles[CurrentIndex].HasBag())
			{
				return false;
			}
			else if (!NewItemData->IsBag() && (!Tiles[CurrentIndex].HasBag() || Tiles[CurrentIndex].HasItem()))
			{
				return false;
			}
		}
	}
	return true;
}

void UMSBackpackGridWidget::AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	FillTilesWithItem(NewItemData, TopLeftIndex);

	int32 TileX = 0;
	int32 TileY = 0;
	IndexToTile(TopLeftIndex, TileX, TileY);

	BackpackComponent->AddBackpackItem(NewItemData, TopLeftIndex);
}

void UMSBackpackGridWidget::AddItemBack(UMSItemData* NewItemData)
{
	auto Items = BackpackComponent->GetItems();

	if (Items.Contains(NewItemData))
	{
		AddThisItemAt(NewItemData, Items[NewItemData]);
	}
}
