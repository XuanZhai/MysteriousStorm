// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemWidget.h"
#include "Components/SizeBox.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MysteriousStorm/Character/MSCharacter.h"

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

void UMSItemWidget::CallOnItemRemoved()
{
	RemoveFromParent();

	if (OnItemRemoved.IsBound())
	{
		OnItemRemoved.Broadcast(ItemPayload->ItemData);
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

void UMSItemWidget::RotateUI()
{
	ItemPayload->ItemData->RotateDegree += 0.25f;

	if (ItemPayload->ItemData->RotateDegree >= 1.0f)
	{
		ItemPayload->ItemData->RotateDegree = 0.0f;
	}

	int32 temp = ItemPayload->ItemData->XUISize;
	ItemPayload->ItemData->XUISize = ItemPayload->ItemData->YUISize;
	ItemPayload->ItemData->YUISize = temp;

	if (UIMaterial)
	{
		UIMaterial->SetScalarParameterValue("RotationAngle", ItemPayload->ItemData->RotateDegree);
	}
}

void UMSItemWidget::UseItem()
{
	AMSCharacter* MainCharacter = GetOwningPlayer() ? Cast<AMSCharacter>(GetOwningPlayer()) : nullptr;

	if (MainCharacter && ItemPayload && MainCharacter->TryUseItem(ItemPayload->ItemData))
	{
		CallOnItemRemoved();
	}
}