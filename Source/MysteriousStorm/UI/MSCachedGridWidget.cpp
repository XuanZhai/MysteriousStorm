// Fill out your copyright notice in the Description page of Project Settings.


#include "MSCachedGridWidget.h"
#include "MSItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "Blueprint/DragDropOperation.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MysteriousStorm/UI/MSBackpackWidget.h"

void UMSCachedGridWidget::Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent)
{
	TileSize = NewTileSize;
	BackpackComponent = NewBackpackComponent;

	if (!BackpackComponent)
	{
		return;
	}

	ColumnNum = BackpackComponent->CachedColumnNumber;
	RowNum = BackpackComponent->CachedRowNumber;
	CachedTiles.SetNum(ColumnNum * RowNum);

	if (GridBorder)
	{
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			CanvasPanelSlot->SetSize(FVector2D(TileSize * ColumnNum, TileSize * RowNum));
		}
	}

	CreateLineSegment();
	Refresh();

	BackpackComponent->OnBackpackChanged.AddDynamic(this, &UMSCachedGridWidget::Refresh);
	BackpackComponent->OnBackpackOpened.AddDynamic(this,&UMSCachedGridWidget::UpdateCachedTiles);
}

void UMSCachedGridWidget::Refresh()
{
	if (!GridPanel || !BackpackComponent)
	{
		return;
	}

	GridPanel->ClearChildren();

	const TMap<UMSItemData*, int32>& NewItems = BackpackComponent->GetCachedItem();
	for (const auto& Item : NewItems)
	{
		int32 TileX = 0;
		int32 TileY = 0;
		IndexToTile(Item.Value, TileX, TileY, ColumnNum);

		UUserWidget* NewWidget = CreateWidget(this, ItemWidgetClass);

		if (UMSItemWidget* NewItemWidget = NewWidget ? Cast<UMSItemWidget>(NewWidget) : nullptr)
		{
			NewItemWidget->SetTileSize(TileSize);
			NewItemWidget->SetItemData(Item.Key,EGridType::CachedGrid);
			NewItemWidget->OnItemRemoved.AddUniqueDynamic(this, &UMSCachedGridWidget::OnItemRemoved);
		}

		auto PanelSlot = GridPanel->AddChild(NewWidget);
		if (UCanvasPanelSlot* CanvasPanelSlot = PanelSlot ? Cast<UCanvasPanelSlot>(PanelSlot) : nullptr)
		{
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetPosition(FVector2D(TileX * TileSize, TileY * TileSize));
		}
	}
}

bool UMSCachedGridWidget::IsItemAvailableToPut(UMSItemData* TargetItem) const
{
	if (BackpackComponent && TargetItem)
	{
		return IsAvailableForNewItem(TargetItem,DropItemTopLeftTile, CachedTiles, ColumnNum,RowNum);
	}
	return false;
}

void UMSCachedGridWidget::OnItemRemoved(UMSItemData* TargetItemData)
{
	if (BackpackComponent && TargetItemData)
	{
		BackpackComponent->RemoveItem(TargetItemData,true);
	}
}

void UMSCachedGridWidget::MousePositionInTile(FVector2D MousePosition, bool& bIsRight, bool& bIsBottom)  const
{
	bIsRight = ((int)MousePosition.X % (int)TileSize) > ((int)TileSize / 2); 
	bIsBottom = ((int)MousePosition.Y % (int)TileSize) > ((int)TileSize / 2);
}

UMSItemData* UMSCachedGridWidget::GetItemDataFromDragDropOperation(UDragDropOperation* InOperation) const
{
	if (InOperation)
	{
		UMSDragPayload* DragPayload = IsValid(InOperation->Payload) ? Cast<UMSDragPayload>(InOperation->Payload) : nullptr;

		if (IsValid(DragPayload))
		{
			return IsValid(DragPayload->ItemData) ? Cast<UMSItemData>(DragPayload->ItemData) : nullptr;
		}
	}
	return nullptr;
}

bool UMSCachedGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UMSItemData* Payload = GetItemDataFromDragDropOperation(InOperation);

	if (IsItemAvailableToPut(Payload))
	{
		AddThisItemAt(Payload,DropItemTopLeftTile);
	}
	else
	{
		TryAddThisItem(Payload);
	}

	return true;
}

bool UMSCachedGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	auto ScreenSpacePosition = InDragDropEvent.GetScreenSpacePosition();
	auto LocalScreenSpacePosition = InGeometry.AbsoluteToLocal(ScreenSpacePosition);

	bool bIsRight = false;
	bool bIsBottom = false;
	MousePositionInTile(LocalScreenSpacePosition,bIsRight,bIsBottom);

	UMSItemData* Payload = GetItemDataFromDragDropOperation(InOperation);

	if (!Payload)
	{
		return false;
	}

	int32 XPos = Payload->XUISize - (bIsRight ? 1 : 0);
	int32 YPos = Payload->YUISize - (bIsBottom ? 1 : 0);

	XPos = FMath::Clamp(XPos,0, XPos);
	YPos = FMath::Clamp(YPos, 0, YPos);

	int32 XMousePosToTile = (int)(LocalScreenSpacePosition.X / TileSize);
	int32 YMousePosToTile = (int)(LocalScreenSpacePosition.Y / TileSize);

	XMousePosToTile -= (XPos/2);
	YMousePosToTile -= (YPos/2);

	XMousePosToTile = FMath::Clamp(XMousePosToTile, 0, ColumnNum);
	XMousePosToTile = FMath::Clamp(XMousePosToTile, 0, RowNum);

	TileToIndex(XMousePosToTile,YMousePosToTile,DropItemTopLeftTile,ColumnNum);

	return true;
}

void UMSCachedGridWidget::ClearCachedTiles()
{
	for (auto& Tile : CachedTiles)
	{
		Tile = nullptr;
	}

	 BackpackComponent->ClearCachedItem();
}

void UMSCachedGridWidget::UpdateCachedTiles()
{
	auto OldCachedItems = BackpackComponent->GetCachedItem();

	ClearCachedTiles();

	for (const auto& CachedItem : BackpackComponent->GetCachedList())
	{
		if (OldCachedItems.Contains(CachedItem.Key) && IsAvailableForNewItem(CachedItem.Key, OldCachedItems[CachedItem.Key],CachedTiles,ColumnNum,RowNum))
		{
			AddThisItemAt(CachedItem.Key, OldCachedItems[CachedItem.Key]);
		}
		else
		{
			TryAddThisItem(CachedItem.Key);
		}
	}
}

void UMSCachedGridWidget::AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	FillTilesWithItem(NewItemData, TopLeftIndex, CachedTiles, ColumnNum);

	int32 TileX = 0;
	int32 TileY = 0;
	IndexToTile(TopLeftIndex, TileX, TileY, ColumnNum);

	BackpackComponent->AddCachedItem(NewItemData,TopLeftIndex);
}

bool UMSCachedGridWidget::TryAddThisItem(UMSItemData* NewItemData)
{
	if (!BackpackComponent->CanAddThisItem(NewItemData, true))
	{
		return false;
	}

	for (int32 i = 0; i < CachedTiles.Num(); i++)
	{
		if (IsAvailableForNewItem(NewItemData, i, CachedTiles, ColumnNum, RowNum))
		{
			AddThisItemAt(NewItemData, i);
			return true;
		}
	}
	return false;
}