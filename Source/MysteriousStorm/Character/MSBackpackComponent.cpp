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
	if (!NewItem)
	{
		return;
	}

	CachedPickUpList.Add(NewItem);
}

void UMSBackpackComponent::RemoveFromCachedPickUpList(AMSItemActor* TargetItem)
{
	if (!TargetItem)
	{
		return;
	}

	CachedPickUpList.Remove(TargetItem);
}

#pragma endregion CachedPickUpList

void UMSBackpackComponent::IndexToTile(const int32 InIndex, int32& OutX, int32& OutY) const
{
	OutX = InIndex % ColumnNumber;
	OutY = InIndex / ColumnNumber;
}

void UMSBackpackComponent::TileToIndex(const int32 InX, const int32 InY, int32& OutIndex) const
{
	OutIndex = InX + InY * ColumnNumber;
}

bool UMSBackpackComponent::IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex,TileXStart,TileYStart);

	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	if (TileXStart < 0 || TileYStart < 0) return false;
	if (TileXEnd > ColumnNumber || TileYEnd > RowNumber) return false;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = x + y * ColumnNumber;

			if (!Tiles.IsValidIndex(CurrentIndex))
			{
				return false;
			}
			else if (Tiles[CurrentIndex] != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

void UMSBackpackComponent::FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex)
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
			int32 CurrentIndex = x + y * ColumnNumber;

			if (!Tiles.IsValidIndex(CurrentIndex))
			{
				UE_LOG(LogTemp,Error, TEXT("Add Fill Tiles Out of bound for %d"), TopLeftIndex);
			}
			Tiles[CurrentIndex] = NewItemData;
		}
	}
}

bool UMSBackpackComponent::CanAddThisItem(UMSItemData* NewItemData) const
{
	if (!NewItemData)
	{
		return false;
	}

	return true;
}

bool UMSBackpackComponent::TryAddThisItem(UMSItemData* NewItemData)
{
	if (!CanAddThisItem(NewItemData))
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

void UMSBackpackComponent::AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	FillTilesWithItem(NewItemData, TopLeftIndex);

	int32 TileX = 0;
	int32 TileY = 0;
	IndexToTile(TopLeftIndex, TileX, TileY);

	Items.Add({ NewItemData, TopLeftIndex });

	if (NewItemData->IsWeapon())
	{
		WeaponList.Add(NewItemData);
	}

	NeedRefresh = true;
}

void UMSBackpackComponent::RemoveItem(UMSItemData* TargetItem)
{
	for (auto& Tile : Tiles)
	{
		if (Tile == TargetItem)
		{
			Tile = nullptr;
		}
	}

	Items.Remove(TargetItem);

	NeedRefresh = true;
}