// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "MysteriousStorm/Item/MSItemData.h"

void UMSItemWidget::SetSize()
{
	if (ItemPayload && ItemPayload->ItemData)
	{
		Size.X = ItemPayload->ItemData->XUISize * TileSize;
		Size.Y = ItemPayload->ItemData->YUISize * TileSize;
	}
}

void UMSItemWidget::SetItemData(UMSItemData* NewItemData, EGridType NewItemSource)
{
	if (!ItemPayload)
	{
		ItemPayload = NewObject<UMSDragPayload>();
	}

	ItemPayload->ItemData = NewItemData;
	ItemPayload->DragSource = NewItemSource;
}

void UMSItemWidget::CallOnItemRemoved(UMSItemData* TargetItemData)
{
	if (OnItemRemoved.IsBound())
	{
		OnItemRemoved.Broadcast(TargetItemData);
	}
}

void UMSItemWidget::Refresh()
{
	SetSize();

	if (BGSizeBox)
	{
		BGSizeBox->SetHeightOverride(Size.Y);
		BGSizeBox->SetWidthOverride(Size.X);
	}

	if (ItemImage)
	{
		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(ItemImage->Slot))
		{
			CanvasSlot->SetSize(Size);
		}
	}
}