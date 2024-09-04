// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackComponent.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Item/MSBackpack.h"
#include "MysteriousStorm/System/MSGameState.h"

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
	AGameModeBase* GameMode = GetWorld() ? GetWorld()->GetAuthGameMode<AGameModeBase>() : nullptr;
	if (AMSGameState* GS = GameMode ? Cast<AMSGameState>(GameMode->GetGameState<AMSGameState>()) : nullptr)
	{
		AMSItemActor* OutActor = nullptr;
		GS->SetGamePaused(true);
	}

	if (OnBackpackOpened.IsBound())
	{
		OnBackpackOpened.Broadcast();
	}
	NeedRefresh = true; 
}

void UMSBackpackComponent::CloseBackpack()
{
	AGameModeBase* GameMode = GetWorld() ? GetWorld()->GetAuthGameMode<AGameModeBase>() : nullptr;
	if (AMSGameState* GS = GameMode ? Cast<AMSGameState>(GameMode->GetGameState<AMSGameState>()) : nullptr)
	{
		AMSItemActor* OutActor = nullptr;
		GS->SetGamePaused(false);
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

void UMSBackpackComponent::AddBackpackItem(UMSItemData* NewItemData, int32 TopLeftIndex, const TSet<UMSItemData*>& BackpackData)
{
	Items.Add({NewItemData,TopLeftIndex});

	if (NewItemData->IsBag())
	{
		UMSBackpack* bag = NewObject<UMSBackpack>();
		bag->SetBagData(NewItemData);
		Bags.Add(bag);
	}
	else
	{
		if (NewItemData->IsWeapon())
		{
			Weapons.Add(NewItemData);
		}

		for (const auto& BagData : BackpackData)
		{
			if (UMSBackpack* Backpack = GetBackpackFromItemData(BagData))
			{
				Backpack->AddNewItem(NewItemData);
			}
		}
	}

	CachedItems.Remove(NewItemData);
	
	if (CachedPickUpList.Contains(NewItemData) && IsValid(CachedPickUpList[NewItemData]))
	{
		CachedPickUpList[NewItemData]->Destroy();
		CachedPickUpList.Remove(NewItemData);
	}

	NeedRefresh = true;
}

void UMSBackpackComponent::RemoveItem(UMSItemData* TargetItem, bool bSpawnNewItem)
{
	if (!TargetItem || !Items.Contains(TargetItem))
	{
		return;
	}

	Items.Remove(TargetItem);

	if (TargetItem->IsBag())
	{
		TSet<UMSBackpack*> TempBag;
		for (const auto& Bag : Bags)
		{
			if (Bag->GetBagData() != TargetItem)
			{
				TempBag.Add(Bag);
			}
		}
		Bags = TempBag;
	}
	else 
	{
		if (TargetItem->IsWeapon())
		{
			Weapons.Remove(TargetItem);
		}

		for (const auto& Bag : Bags)
		{
			if (Bag->GetBagData() == TargetItem)
			{
				Bag->RemoveItem(TargetItem);
			}
		}
	}

	if (OnItemRemovedFromBackpack.IsBound())
	{
		OnItemRemovedFromBackpack.Broadcast(TargetItem);
	}

	if(bSpawnNewItem)
	{
		AGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGameModeBase>();
		if(AMSGameState* GS = GameMode ? Cast<AMSGameState>(GameMode->GetGameState<AMSGameState>()) : nullptr)
		{
			AMSItemActor* OutActor = nullptr;
			GS->TrySpawnItemActorFromData(TargetItem, GetOwner(), OutActor, true);
		}
	}

	NeedRefresh = true;
}

bool UMSBackpackComponent::DoesItemExist(const int32 ItemID) const
{
	for (const auto& Item : Items)
	{
		if (IsValid(Item.Key) && Item.Key->ID == ItemID)
		{
			return true;
		}
	}

	return false;
}

UMSBackpack* UMSBackpackComponent::GetBackpackFromItemData(const UMSItemData* TargetItem) const
{
	for (const auto& Bag : Bags)
	{
		if (Bag->GetBagData() == TargetItem)
		{
			return Bag;
		}
	}
	return nullptr;
}