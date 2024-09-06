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
	if (DoesEffectExist(NewEffect))
	{
		return;
	}

	for (const auto& Item : Items)
	{
		Item->AddEffect(NewEffect);
	}
}

void UMSBackpack::RemoveEffect(EMSEffect TargetEffect)
{
	if (!DoesEffectExist(TargetEffect))
	{
		return;
	}

	for (const auto& Item : Items)
	{
		Item->RemoveEffect(TargetEffect);
	}
}

bool UMSBackpack::DoesEffectExist(EMSEffect TargetEffect) const
{
	if (Items.IsEmpty())
	{
		return false;
	}

	return Items.Array()[0]->DoesEffectExist(TargetEffect);
}