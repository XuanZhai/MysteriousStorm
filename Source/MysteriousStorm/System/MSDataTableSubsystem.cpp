// Fill out your copyright notice in the Description page of Project Settings.


#include "MSDataTableSubsystem.h"
#include "MSItemTableRow.h"
#include "MSWeaponTableRow.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Engine/DataTable.h"

void UMSDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	TArray<FSoftObjectPath> Paths = 
	{
		ItemTablePath,
		WeaponTablePath
	};

	// TODO: Change it to Async
	ItemTable = Cast<UDataTable>(ItemTablePath.TryLoad());
	WeaponTable = Cast<UDataTable>(WeaponTablePath.TryLoad());

//	StreamableHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
// 		Paths, [this]()
// 		{
// 
// 			ItemTable = Cast<UDataTable>(ItemTablePath.ResolveObject());
// 			WeaponTable = Cast<UDataTable>(WeaponTablePath.ResolveObject());
// 
// 			if (OnTableLoaded.IsBound())
// 			{
// 				OnTableLoaded.Broadcast(this);
// 			}
// 		});

}

void UMSDataTableSubsystem::OnDataTableLoaded()
{

}

void UMSDataTableSubsystem::Deinitialize()
{

}

bool UMSDataTableSubsystem::TryGetRowByItemID(const int32 ItemID, struct FMSItemTableRow& OutRow) const
{
	if (ItemTable)
	{
		if (FMSItemTableRow* Row = ItemTable->FindRow<FMSItemTableRow>(FName(FString::FromInt(ItemID)), TEXT("Context")))
		{
			OutRow = *Row;
			return true;
		}
	}
	return false;
}

bool UMSDataTableSubsystem::TryGetWeaponConfigByItemID(const int32 ItemID, struct FMSWeaponTableRow& OutRow) const
{
	if (WeaponTable)
	{
		if (FMSWeaponTableRow* Row = WeaponTable->FindRow<FMSWeaponTableRow>(FName(FString::FromInt(ItemID)), TEXT("Context")))
		{
			OutRow = *Row;
			return true;
		}
	}
	return false;
}
