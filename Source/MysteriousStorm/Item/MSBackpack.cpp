// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpack.h"

void UMSBackpack::AddNewItem(UMSItemData* NewItem)
{
	Items.Add(NewItem);
}

void UMSBackpack::RemoveItem(UMSItemData* TargetItem)
{
	Items.Remove(TargetItem);
}