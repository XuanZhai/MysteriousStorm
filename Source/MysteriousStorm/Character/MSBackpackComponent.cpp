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
	//Tiles.SetNum(ColumnNumber * RowNumber);
	//CachedTiles.SetNum(CachedColumnNumber * CachedRowNumber);
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

void UMSBackpackComponent::AddCachedItem(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	CachedItems.Add({ NewItemData,TopLeftIndex });
	NeedRefresh = true;
}

#pragma endregion CachedPickUpList

void UMSBackpackComponent::OpenBackpack()
{
	if (OnBackpackOpened.IsBound())
	{
		OnBackpackOpened.Broadcast();
	}
	NeedRefresh = true;
}

void UMSBackpackComponent::CloseBackpack()
{

}

bool UMSBackpackComponent::CanAddThisItem(UMSItemData* NewItemData, bool bIsBackpack) const
{
	if (!NewItemData)
	{
		return false;
	}

	return true;
}

void UMSBackpackComponent::AddBackpackItem(UMSItemData* NewItemData, int32 TopLeftIndex)
{
	Items.Add({NewItemData,TopLeftIndex});
	NeedRefresh = true;
}

// bool UMSBackpackComponent::TryAddThisItem(UMSItemData* NewItemData, TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum)
// {
// 	if (!CanAddThisItem(NewItemData,true))
// 	{
// 		return false;
// 	}
// 
// 	for (int32 i = 0; i < InTiles.Num(); i++)
// 	{
// 		if (IsAvailableForNewItem(NewItemData, i, InTiles,ColNum, RowNum))
// 		{
// 			AddThisItemAt(NewItemData, i, InTiles, ColNum, RowNum);
// 			return true;
// 		}
// 	}
// 	return false;
// }

// void UMSBackpackComponent::AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex, TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum)
// {
// 	FillTilesWithItem(NewItemData, TopLeftIndex,InTiles,ColNum);
// 
// 	int32 TileX = 0;
// 	int32 TileY = 0;
// 	IndexToTile(TopLeftIndex, TileX, TileY,ColNum);
// 
// 	if (InTiles == Tiles)
// 	{
// 		Items.Add({ NewItemData, TopLeftIndex });
// 		if (NewItemData->IsWeapon())
// 		{
// 			WeaponList.Add(NewItemData);
// 		}
// 	}
// 	else
// 	{
// 		CachedItems.Add({ NewItemData, TopLeftIndex });
// 	}
// 
// 	NeedRefresh = true;
//}

void UMSBackpackComponent::RemoveItem(UMSItemData* TargetItem, bool bIsBackpack)
{
// 	if (bIsBackpack) 
// 	{
// 		for (auto& Tile : Tiles)
// 		{
// 			if (Tile == TargetItem)
// 			{
// 				Tile = nullptr;
// 			}
// 		}
// 		Items.Remove(TargetItem);
// 	}
// 	else
// 	{
// 		for (auto& Tile : CachedTiles)
// 		{
// 			if (Tile == TargetItem)
// 			{
// 				Tile = nullptr;
// 			}
// 		}
// 		CachedItems.Remove(TargetItem);
// 	}
// 
// 	NeedRefresh = true;
}