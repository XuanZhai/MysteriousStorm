// Fill out your copyright notice in the Description page of Project Settings.


#include "MSSpecialItemActor.h"
#include "MSSpecialItemData.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSItemTableRow.h"

void AMSSpecialItemActor::InitItemData()
{
	UGameInstance* GameInstance = GetGameInstance();
	UMSDataTableSubsystem* TableSubsystem = GameInstance->GetSubsystem<UMSDataTableSubsystem>();

	if (!TableSubsystem)
	{
		return;
	}

	UMSSpecialItemData* SpecialItemData = NewObject<UMSSpecialItemData>();

	FMSItemTableRow Row;
	if (SpecialItemData && TableSubsystem->TryGetRowByItemID(ItemID, Row))
	{
		SpecialItemData->ID = Row.ID;
		SpecialItemData->Name = Row.Name;
		SpecialItemData->ItemType = Row.ItemType;
		SpecialItemData->UIPath = Row.UIPath;
		SpecialItemData->XUISize = Row.XUISize;
		SpecialItemData->YUISize = Row.YUISize;
		SpecialItemData->AssetBP = Row.AssetBP;
	}
	SpecialItemData->AffectMap = AffectMap;
	SpecialItemData->SpecialItemType = SpecialItemType;
	SpecialItemData->bIsGridType = bIsGridType;
	SpecialItemData->GridEffect = GridEffect;
	SpecialItemData->GridEffectLevel = GridEffectLevel;

	ItemData = SpecialItemData;
}