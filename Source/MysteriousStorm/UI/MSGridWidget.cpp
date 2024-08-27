// Fill out your copyright notice in the Description page of Project Settings.


#include "MSGridWidget.h"
#include "MSItemWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Border.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"

void UMSGridWidget::Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent)
{
	TileSize = NewTileSize;
	BackpackComponent = NewBackpackComponent;

	if (!BackpackComponent)
	{
		return;
	}

	if (bIsCachedBackpack)
	{
		ColumnNum = BackpackComponent->CachedColumnNumber;
		RowNum = BackpackComponent->CachedRowNumber;
	}
	else
	{
		ColumnNum = BackpackComponent->ColumnNumber;
		RowNum = BackpackComponent->RowNumber;
	}

	if (GridBorder)
	{
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			CanvasPanelSlot->SetSize(FVector2D(TileSize* ColumnNum, TileSize * RowNum));
		}
	}

	CreateLineSegment();
	Refresh();

	BackpackComponent->OnBackpackChanged.AddDynamic(this, &UMSGridWidget::Refresh);
}

void UMSGridWidget::Refresh()
{
	if (!GridPanel || !BackpackComponent)
	{
		return;
	}

	GridPanel->ClearChildren();

	const TMap<UMSItemData*, int32>& NewItems = bIsCachedBackpack ? BackpackComponent->GetCachedItems() : BackpackComponent->GetItems();
	UE_LOG(LogTemp, Display, TEXT("Size is %d"), NewItems.Num());

	for (const auto& Item : NewItems)
	{
		int32 TileX = 0;
		int32 TileY = 0;
		BackpackComponent->IndexToTile(Item.Value, TileX, TileY, ColumnNum);

		UUserWidget* NewWidget = CreateWidget(this, ItemWidgetClass);

		if (UMSItemWidget* NewItemWidget = NewWidget ? Cast<UMSItemWidget>(NewWidget) : nullptr)
		{
			NewItemWidget->SetTileSize(TileSize);
			NewItemWidget->SetItemData(Item.Key);
			NewItemWidget->OnItemRemoved.AddUniqueDynamic(this, &UMSGridWidget::OnItemRemoved);
		}

		auto PanelSlot = GridPanel->AddChild(NewWidget);
		if (UCanvasPanelSlot* CanvasPanelSlot = PanelSlot ? Cast<UCanvasPanelSlot>(PanelSlot) : nullptr)
		{
			CanvasPanelSlot->SetAutoSize(true);
			CanvasPanelSlot->SetPosition(FVector2D(TileX*TileSize,TileY*TileSize));
		}
		 


	}
}


bool UMSGridWidget::IsPayloadAvailable_Implementation(UMSItemData* Payload) const
{
	return true;
	//if (!Payload || !BackpackComponent)
	//{
	//	return false;
	//}

	//return BackpackComponent->IsAvailableForNewItem_Implementation(Payload, DropItemTopLeftTile, );
}

void UMSGridWidget::OnItemRemoved_Implementation(UMSItemData* TargetItemData)
{
	//if (BackpackComponent)
	//{
	//	BackpackComponent->RemoveItem(TargetItemData);
	//}
}
