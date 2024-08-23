// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackComponent.h"
#include "MysteriousStorm/Item//MSItemActor.h"

// Sets default values for this component's properties
UMSBackpackComponent::UMSBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UMSBackpackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
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

bool UMSBackpackComponent::IsRoomForNewItem(const FMSItemData& NewItemData, int32 TopLeftIndex) const
{
	int32 TileXStart = TopLeftIndex % ColumnNumber;
	int32 TileYStart = TopLeftIndex / ColumnNumber;
	int32 TileXEnd = TileXStart + NewItemData.XUISize - 1;
	int32 TileYEnd = TileYStart + NewItemData.YUISize - 1;


	if (TileXStart < 0 || TileYStart < 0) return false;
	if (TileXEnd >= ColumnNumber || TileYEnd >= RowNumber) return false;


	// TODO: 


	return true;

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

	return true;
}