// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackComponent.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "MysteriousStorm/Item/MSItemData.h"

// Sets default values for this component's properties
UMSBackpackComponent::UMSBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	NeedRefresh = false;
}


// Called when the game starts
void UMSBackpackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	Tiles.SetNum(ColumnNumber * RowNumber);
	CachedTiles.SetNum(CachedColumnNumber * CachedRowNumber);
}


// Called every frame
void UMSBackpackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (NeedRefresh && OnBackpackChanged.IsBound())
	{
		OnBackpackChanged.Broadcast();
		NeedRefresh = false;
	}
}

#pragma region CachedPickUpList

void UMSBackpackComponent::AddToCachedPickUpList(AMSItemActor* NewItem)
{
	if (!NewItem || !NewItem->GetItemData())
	{
		return;
	}
	CachedPickUpList.Add({ NewItem->GetItemData(), NewItem});
}

void UMSBackpackComponent::RemoveFromCachedPickUpList(AMSItemActor* TargetItem)
{
	if (!TargetItem || !TargetItem->GetItemData())
	{
		return;
	}
	CachedPickUpList.Remove(TargetItem->GetItemData());
}

void UMSBackpackComponent::ClearCachedPickUpList()
{
	for (auto& Tile : CachedTiles)
	{
		Tile = nullptr;
	}
}

bool UMSBackpackComponent::TryFillCachedTiles()
{
	ClearCachedPickUpList();

	for (auto& CachedItem : CachedPickUpList)
	{
		TryAddThisItem(CachedItem.Key, CachedTiles, CachedColumnNumber, CachedRowNumber);
	}
	return true;
}

#pragma endregion CachedPickUpList

void UMSBackpackComponent::IndexToTile(const int32 InIndex, int32& OutX, int32& OutY, const int32 ColumnNum) const
{
	OutX = InIndex % ColumnNum;
	OutY = InIndex / ColumnNum;
}

void UMSBackpackComponent::TileToIndex(const int32 InX, const int32 InY, int32& OutIndex, const int32 ColumnNum) const
{
	OutIndex = InX + InY * ColumnNum;
}

bool UMSBackpackComponent::IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex, const TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex,TileXStart,TileYStart, ColNum);

	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	if (TileXStart < 0 || TileYStart < 0) return false;
	if (TileXEnd > ColNum || TileYEnd > RowNum) return false;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex, ColNum);

			if (!InTiles.IsValidIndex(CurrentIndex))
			{
				return false;
			}
			else if (InTiles[CurrentIndex] != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

void UMSBackpackComponent::FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex, TArray<UMSItemData*>& InTiles, const int32 ColNum)
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart, ColNum);
	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex, ColNum);

			if (InTiles.IsValidIndex(CurrentIndex))
			{
				InTiles[CurrentIndex] = NewItemData;
			}
		}
	}
}

bool UMSBackpackComponent::CanAddThisItem(UMSItemData* NewItemData, bool bIsBackpack) const
{
	if (!NewItemData)
	{
		return false;
	}

	return true;
}

bool UMSBackpackComponent::TryAddThisItem(UMSItemData* NewItemData, TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum)
{
	if (!CanAddThisItem(NewItemData,true))
	{
		return false;
	}

	for (int32 i = 0; i < InTiles.Num(); i++)
	{
		if (IsAvailableForNewItem(NewItemData, i, InTiles,ColNum, RowNum))
		{
			AddThisItemAt(NewItemData, i, InTiles, ColNum, RowNum);
			return true;
		}
	}
	return false;
}

void UMSBackpackComponent::AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex, TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum)
{
	FillTilesWithItem(NewItemData, TopLeftIndex,InTiles,ColNum);

	int32 TileX = 0;
	int32 TileY = 0;
	IndexToTile(TopLeftIndex, TileX, TileY,ColNum);

	if (InTiles == Tiles)
	{
		Items.Add({ NewItemData, TopLeftIndex });
		if (NewItemData->IsWeapon())
		{
			WeaponList.Add(NewItemData);
		}
	}
	else
	{
		CachedItems.Add({ NewItemData, TopLeftIndex });
	}

	NeedRefresh = true;
}

void UMSBackpackComponent::RemoveItem(UMSItemData* TargetItem, bool bIsBackpack)
{
	if (bIsBackpack) 
	{
		for (auto& Tile : Tiles)
		{
			if (Tile == TargetItem)
			{
				Tile = nullptr;
			}
		}
		Items.Remove(TargetItem);
	}
	else
	{
		for (auto& Tile : CachedTiles)
		{
			if (Tile == TargetItem)
			{
				Tile = nullptr;
			}
		}
		CachedItems.Remove(TargetItem);
	}

	NeedRefresh = true;
}