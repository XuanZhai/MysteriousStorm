// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackWidget.h"
#include "MSItemWidget.h"
#include "MSGridWidget.h"
#include "MSCachedGridWidget.h"
#include "MSBackpackGridWidget.h"
#include "Blueprint/DragDropOperation.h"

void UMSBackpackWidget::InitializeGrid()
{
	WB_GridWidget->Initialization(TileSize,BackpackComponent);
	WB_CachedGridWidget->Initialization(TileSize,BackpackComponent);
	WB_GridWidget->OnMouseDropped.AddUniqueDynamic(this, &UMSBackpackWidget::OnMouseDroppedCallback);
	WB_CachedGridWidget->OnMouseDropped.AddUniqueDynamic(this, &UMSBackpackWidget::OnMouseDroppedCallback);
}

bool UMSBackpackWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UMSDragPayload* Payload = InOperation->Payload ? Cast<UMSDragPayload>(InOperation->Payload) : nullptr;

	if (!Payload)
	{
		return false;
	}

	EGridType GridSource = Payload->DragSource;

	if (GridSource == EGridType::CachedGrid)
	{
		WB_CachedGridWidget->AddItemBack(Payload->ItemData);
		return true;
	}
	else if (GridSource == EGridType::BackpackGrid)
	{
		WB_GridWidget->AddItemBack(Payload->ItemData);
		return true;
	}

	return false;
}

void UMSBackpackWidget::OnMouseDroppedCallback()
{
	WB_GridWidget->bDrawDropLocation = false;
	WB_CachedGridWidget->bDrawDropLocation =false;
}