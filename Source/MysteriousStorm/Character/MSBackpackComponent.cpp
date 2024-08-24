// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackComponent.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "MysteriousStorm/Item/MSItemData.h"

// Sets default values for this component's properties
UMSBackpackComponent::UMSBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Tiles.SetNum(ColumnNumber*RowNumber);
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

	// ...
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

bool UMSBackpackComponent::IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex,TileXStart,TileYStart);

	int32 TileXEnd = TileXStart + NewItemData->XUISize - 1;
	int32 TileYEnd = TileYStart + NewItemData->YUISize - 1;

	if (TileXStart < 0 || TileYStart < 0) return false;
	if (TileXEnd >= ColumnNumber || TileYEnd >= RowNumber) return false;

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
	int32 TileXEnd = TileXStart + NewItemData->XUISize - 1;
	int32 TileYEnd = TileYStart + NewItemData->YUISize - 1;

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

bool UMSBackpackComponent::CanPickUpThisItem(AMSItemActor* NewItem) const
{
	if (!NewItem)
	{
		return false;
	}

	return true;
}

bool UMSBackpackComponent::TryPickUpThisItem(AMSItemActor* NewItem)
{
	if (!CanPickUpThisItem(NewItem))
	{
		return false;
	}

	UMSItemData* ItemData = NewItem->GetItemData();
	for (int32 i = 0; i < Tiles.Num(); i++)
	{
		if (IsAvailableForNewItem(ItemData, i))
		{
			NewItem->Destroy();
			FillTilesWithItem(ItemData,i);

			Items.Add(ItemData);
			if (NewItem->IsWeapon())
			{
				Weapons.Add(ItemData);
			}

			return true;
		}
	}
	return false;
}