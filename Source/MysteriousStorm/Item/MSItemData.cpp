// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemData.h"

FMSItemData::FMSItemData()
{
	ItemID = 0;
	Count = 0;
	XUISize = 0;
	YUISize = 0;
	ItemType = EItemType::MAX;
}

FMSItemData::~FMSItemData()
{
}
