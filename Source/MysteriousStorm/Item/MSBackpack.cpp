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

void UMSBackpack::AddEffect(EMSEffect NewEffect)
{	
	if (Effects.Contains(NewEffect))
	{
		return;
	}

	for (const auto& Item : Items)
	{
		Item->AddEffect(NewEffect);
	}

	Effects.Add(NewEffect);
}

void UMSBackpack::RemoveEffect(EMSEffect TargetEffect)
{
	if (!Effects.Contains(TargetEffect))
	{
		return;
	}

	for (const auto& Item : Items)
	{
		Item->RemoveEffect(TargetEffect);
	}

	Effects.Remove(TargetEffect);
}