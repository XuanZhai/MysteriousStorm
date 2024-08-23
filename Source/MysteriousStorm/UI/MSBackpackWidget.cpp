// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackWidget.h"
#include "MSCachedPickUpItemWidget.h"
#include "MysteriousStorm/Item//MSItemActor.h"
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

	UGameInstance* GameInstance = GetGameInstance();
	UMSDataTableSubsystem* TableSubsystem = GameInstance->GetSubsystem<UMSDataTableSubsystem>();

	if (BackpackComponent && TableSubsystem)
	{
		TArray<AMSItemActor*> CachedPickUpList = BackpackComponent->GetCachedPickUpList();

		for(AMSItemActor * CacheItem : CachedPickUpList)
		{
			if (!CacheItem)
			{
				continue;
			}

			UMSCachedPickUpItemWidget* CachedItemWidget = CreateWidget<UMSCachedPickUpItemWidget>(this, UMSCachedPickUpItemWidget::StaticClass());
			if (CachedItemWidget)
			{
				const FMSItemData& ItemData = CacheItem->GetItemData();
				FMSItemTableRow Row;

				if (TableSubsystem->TryGetRowByItemID(ItemData.ItemID, Row))
				{
					CachedItemWidget->SetItemName(Row.Name);
					CachedItemWidget->SetItemImage(Row.UIPath);
					CachedItemWidget->ParentListView = CachedPickUpListView;
					CachedPickUpListView->AddItem(CachedItemWidget);
				}
			}
		}
	}

	CachedPickUpListView->RequestRefresh();
}