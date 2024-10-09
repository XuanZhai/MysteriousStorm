// Fill out your copyright notice in the Description page of Project Settings.


#include "MSBackpackWidget.h"
#include "MSItemWidget.h"
#include "MSGridWidget.h"
#include "MSCachedGridWidget.h"
#include "MSBackpackGridWidget.h"
#include "MSStorageWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "Components/CanvasPanel.h"

void UMSBackpackWidget::InitializeGrid()
{
	WB_GridWidget->Initialization(TileSize,BackpackComponent);
	WB_CachedGridWidget->Initialization(TileSize,BackpackComponent);
	WB_StorageGridWidget->Initialization(TileSize, BackpackComponent);
	StorageGridCanvas->SetVisibility(ESlateVisibility::Collapsed);

	WB_GridWidget->OnMouseDropped.AddUniqueDynamic(this, &UMSBackpackWidget::OnMouseDroppedCallback);
	WB_CachedGridWidget->OnMouseDropped.AddUniqueDynamic(this, &UMSBackpackWidget::OnMouseDroppedCallback);
	WB_StorageGridWidget->OnMouseDropped.AddUniqueDynamic(this, &UMSBackpackWidget::OnMouseDroppedCallback);

	WB_CachedGridWidget->NeedDropBack.AddUniqueDynamic(WB_GridWidget, &UMSBackpackGridWidget::AddItemBack);
	WB_StorageGridWidget->NeedDropBack.AddUniqueDynamic(WB_GridWidget, &UMSBackpackGridWidget::AddItemBack);
	WB_GridWidget->NeedDropBack.AddUniqueDynamic(WB_CachedGridWidget, &UMSCachedGridWidget::AddItemBack);
	WB_GridWidget->PutChildToGround.AddUniqueDynamic(WB_CachedGridWidget, &UMSCachedGridWidget::AddChildItem);

	BackpackComponent->OnEnterStorageBox.AddUniqueDynamic(this, &UMSBackpackWidget::EnterStorageBox);
	BackpackComponent->OnLeaveStorageBox.AddUniqueDynamic(this, &UMSBackpackWidget::LeaveStorageBox);
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

void UMSBackpackWidget::EnterStorageBox(AMSStorageBox* NewBox)
{
	CachedGridCanvas->SetVisibility(ESlateVisibility::Collapsed);
	StorageGridCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UMSBackpackWidget::LeaveStorageBox(AMSStorageBox* OldBox)
{
	CachedGridCanvas->SetVisibility(ESlateVisibility::Visible);
	StorageGridCanvas->SetVisibility(ESlateVisibility::Collapsed);
}