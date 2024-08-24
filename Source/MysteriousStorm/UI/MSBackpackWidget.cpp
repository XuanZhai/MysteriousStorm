// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackWidget.h"
#include "MSCachedPickUpItemWidget.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Item/MSItemActor.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSItemTableRow.h"


void UMSBackpackWidget::RefreshCachedPickUpListView()
{
	if (!CachedPickUpListView)
	{
		return;
	}

	CachedPickUpListView->ClearListItems();

	if (BackpackComponent)
	{
		TArray<AMSItemActor*> CachedPickUpList = BackpackComponent->GetCachedPickUpList();

		for(AMSItemActor * CacheItem : CachedPickUpList)
		{
			if (!CacheItem)
			{
				continue;
			}

			if (UMSItemData* ItemData = CacheItem->GetItemData())
			{
				CachedPickUpListView->AddItem(ItemData);
			}
		}
	}

	CachedPickUpListView->RequestRefresh();
}