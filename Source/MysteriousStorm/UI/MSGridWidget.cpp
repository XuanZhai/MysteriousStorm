// Fill out your copyright notice in the Description page of Project Settings.


#include "MSGridWidget.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MSItemWidget.h"
#include "Blueprint/DragDropOperation.h"

void UMSGridWidget::IndexToTile(const int32 InIndex, int32& OutX, int32& OutY) const
{
	OutX = InIndex % ColumnNum;
	OutY = InIndex / ColumnNum; 
}

void UMSGridWidget::TileToIndex(const int32 InX, const int32 InY, int32& OutIndex) const
{
	OutIndex = InX + InY * ColumnNum;
}

bool UMSGridWidget::IsItemAvailableToPut(UMSItemData* TargetItem) const
{
	if (BackpackComponent && TargetItem)
	{
		return IsAvailableForNewItem(TargetItem, DropItemTopLeftTile);
	}
	return false;
}

void UMSGridWidget::FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart);
	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex);

			if (Tiles.IsValidIndex(CurrentIndex))
			{
				if (NewItemData->IsBag())
				{
					Tiles[CurrentIndex].SetBag(NewItemData);
				}
				else 
				{
					Tiles[CurrentIndex].SetItem(NewItemData);
				}
			}
		}
	}
}

bool UMSGridWidget::TryAddThisItem(UMSItemData* NewItemData)
{
	if (!BackpackComponent->CanAddThisItem(NewItemData, true))
	{
		return false;
	}

	for (int32 i = 0; i < Tiles.Num(); i++)
	{
		if (IsAvailableForNewItem(NewItemData, i))
		{
			AddThisItemAt(NewItemData, i);
			return true;
		}
	}
	return false;
}

UMSItemData* UMSGridWidget::GetItemDataFromDragDropOperation(UDragDropOperation* InOperation) const
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

EGridType UMSGridWidget::GetDragSourceFromDragDropOperation(UDragDropOperation* InOperation) const
{
	if (InOperation)
	{
		UMSDragPayload* DragPayload = IsValid(InOperation->Payload) ? Cast<UMSDragPayload>(InOperation->Payload) : nullptr;

		if (IsValid(DragPayload))
		{
			return DragPayload->DragSource;
		}
	}
	return EGridType::DEFAULT;
}
