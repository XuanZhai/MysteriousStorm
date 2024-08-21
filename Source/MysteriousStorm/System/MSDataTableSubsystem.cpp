// Fill out your copyright notice in the Description page of Project Settings.


#include "MSDataTableSubsystem.h"
#include "MSItemTableRow.h"
#include "Engine/DataTable.h"

void UMSDataTableSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	ItemTable = ItemTableRef.IsValid() ? ItemTableRef.LoadSynchronous() : nullptr;
	WeaponTable = WeaponTableRef.IsValid() ? WeaponTableRef.LoadSynchronous() : nullptr;
}

void UMSDataTableSubsystem::Deinitialize()
{

}

bool UMSDataTableSubsystem::TryGetAssetPathByItemID(const int32 ItemID, FSoftObjectPath& OutObjectPath)
{
	if (!ItemTable)
	{
		return false;
	}

	if (FMSItemTableRow* Row = ItemTable->FindRow<FMSItemTableRow>(FName(FString::FromInt(ItemID)), TEXT("Context")))
	{
		OutObjectPath = Row->AssetPath;
		return true;
	}

	return false;
}