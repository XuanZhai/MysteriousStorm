// Fill out your copyright notice in the Description page of Project Settings.


#include "MSConsumableActor.h"
#include "MSConsumableData.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSItemTableRow.h"

AMSConsumableActor::AMSConsumableActor()
{
	Value = 0.0f;
}

void AMSConsumableActor::InitItemData()
{
	UGameInstance* GameInstance = GetGameInstance();
	UMSDataTableSubsystem* TableSubsystem = GameInstance->GetSubsystem<UMSDataTableSubsystem>();

	if (!TableSubsystem)
	{
		return;
	}

	UMSConsumableData* ConsumableData = NewObject<UMSConsumableData>();

	FMSItemTableRow Row;
	if (ConsumableData && TableSubsystem->TryGetRowByItemID(ItemID, Row))
	{
		ConsumableData->ID = Row.ID;
		ConsumableData->Name = Row.Name;
		ConsumableData->ItemType = Row.ItemType;
		ConsumableData->UIPath = Row.UIPath;
		ConsumableData->XUISize = Row.XUISize;
		ConsumableData->YUISize = Row.YUISize;
		ConsumableData->AssetBP = Row.AssetBP;
	}
	ConsumableData->Value = Value;
	ConsumableData->ConsumableType = ConsumableType;

	ItemData = ConsumableData;
}