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
#include "MysteriousStorm/Item/Weapon/MSWeaponData.h"

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
	BackpackComponent->OnPreBackpackClosed.AddDynamic(this,&UMSBackpackGridWidget::CalculateGridData);
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
			CanvasPanelSlot->SetZOrder(Item.Key->IsBag() ? 0 : 1);
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetPosition(FVector2D(TileX * TileSize, TileY * TileSize));
		}
	}
}

void UMSBackpackGridWidget::OnItemRemoved(UMSItemData* TargetItemData)
{
	if (TargetItemData->IsBag())
	{
		TSet<UMSItemData*> TargetItems;
		RetrieveItemsFromBackpack(TargetItemData,BackpackComponent->GetItems()[TargetItemData],TargetItems);

		for (auto& Tile : Tiles)
		{
			if (TargetItems.Contains(Tile.Item))
			{
				if (PutChildToGround.IsBound())
				{
					PutChildToGround.Broadcast(Tile.Item);
				}
				BackpackComponent->RemoveItem(Tile.Item);
				Tile.ClearItemData();
			}
			if (Tile.Bag == TargetItemData)
			{
				BackpackComponent->RemoveItem(Tile.Bag, false);
				Tile.ClearAllData();
			}
		}

	}
	else 
	{
		BackpackComponent->RemoveItem(TargetItemData,false);
		for (auto& Tile : Tiles)
		{
			if (Tile.Item == TargetItemData)
			{
				Tile.ClearItemData();
			}
		}
	}
// 
// 
// 	for (auto& Tile : Tiles)
// 	{
// 		if (TargetItems.Contains(Tile.Item))
// 		{
// 			Tile.ClearItemData();
// 		}
// 		else if (Tile.Bag == TargetItemData)
// 		{
// 			if (Tile.bHasItem)
// 			{
// 				if (PutChildToGround.IsBound())
// 				{
// 					PutChildToGround.Broadcast(Tile.Item);
// 				}
// 				BackpackComponent->RemoveItem(Tile.Item);
// 			} 
// 			BackpackComponent->RemoveItem(Tile.Bag,false);
// 			Tile.ClearAllData();
// 		}
// 	}
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

	TSet<UMSItemData*> OccupiedBackpacks;
	RetrieveContainedBackpacks(NewItemData,TopLeftIndex,OccupiedBackpacks);

	BackpackComponent->AddBackpackItem(NewItemData, TopLeftIndex, OccupiedBackpacks);
}

void UMSBackpackGridWidget::AddItemBack(UMSItemData* NewItemData)
{
	auto Items = BackpackComponent->GetItems();

	if (Items.Contains(NewItemData))
	{
		AddThisItemAt(NewItemData, Items[NewItemData]);
	}
}

void UMSBackpackGridWidget::RetrieveContainedBackpacks(UMSItemData* TargetItemData, int32 TopLeftIndex, TSet<UMSItemData*>& OutBackpacks)
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart);
	int32 TileXEnd = TileXStart + TargetItemData->XUISize;
	int32 TileYEnd = TileYStart + TargetItemData->YUISize;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex);

			if (Tiles.IsValidIndex(CurrentIndex) && Tiles[CurrentIndex].Bag)
			{
				OutBackpacks.Add(Tiles[CurrentIndex].Bag);
			}
		}
	}
}

void UMSBackpackGridWidget::RetrieveItemsFromBackpack(UMSItemData* TargetBagData, int32 TopLeftIndex, TSet<UMSItemData*>& OutItems)
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart);
	int32 TileXEnd = TileXStart + TargetBagData->XUISize;
	int32 TileYEnd = TileYStart + TargetBagData->YUISize;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex);

			if (Tiles.IsValidIndex(CurrentIndex) && Tiles[CurrentIndex].Item)
			{
				OutItems.Add(Tiles[CurrentIndex].Item);
			}
		}
	}
}

void UMSBackpackGridWidget::CalculateGridData()
{
	float CurrentTime = 0.0f;
	float TotalTime = 0.0f;
	TArray<bool> VisitList;
	VisitList.Init(false,Tiles.Num());

	for (int32 i = 0; i < Tiles.Num(); i++)
	{
		const FTileinfo& Tile = Tiles[i];

		if (VisitList[i])
		{
			continue;
		}
		else if (!Tile.bHasBag)
		{
			VisitList[i] = true;
			continue;
		}
		else if (!Tile.bHasItem)
		{
			CurrentTime += BagTime;
			TotalTime += BagTime;
			VisitList[i] = true;
			continue;
		}

		FillVisitedList(Tile.Item, VisitList, i);
		CurrentTime += ItemTime * (Tile.Item->XUISize * Tile.Item->YUISize);
		TotalTime += ItemTime * (Tile.Item->XUISize * Tile.Item->YUISize);

		if (Tile.Item->IsWeapon())
		{
			if (UMSWeaponData* TargetWeaponData = Cast<UMSWeaponData>(Tile.Item))
			{
				TargetWeaponData->TriggerTimeInRound = CurrentTime;
			}
		}
	}

	const auto& Backpack = BackpackComponent->GetItems();
	for (const auto& Item : Backpack)
	{
		if (Item.Key->IsWeapon())
		{
			if (UMSWeaponData* TargetWeaponData = Cast<UMSWeaponData>(Item.Key))
			{
				TargetWeaponData->TotalRoundTime = TotalTime;
				//UE_LOG(LogTemp,Warning, TEXT("Weapon %s has current time %f and total time %f"), *Item.Key->Name, TargetWeaponData->TriggerTimeInRound, TargetWeaponData->TotalRoundTime);
			}
		}
	}
}

void UMSBackpackGridWidget::FillVisitedList(UMSItemData* ItemData, TArray<bool>& VisitedList, int32 TopLeftIndex) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart);
	int32 TileXEnd = TileXStart + ItemData->XUISize;
	int32 TileYEnd = TileYStart + ItemData->YUISize;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex);
			VisitedList[CurrentIndex] = true;
		}
	}
}