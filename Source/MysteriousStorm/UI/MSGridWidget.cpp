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

	if (GridBorder)
	{
		if (UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridBorder->Slot))
		{
			CanvasPanelSlot->SetSize(FVector2D(TileSize*BackpackComponent->ColumnNumber, TileSize * BackpackComponent->RowNumber));
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

	const TMap<UMSItemData*, int32>& Items = BackpackComponent->GetItems();

	for (const auto& Item : Items)
	{
		int32 TileX = 0;
		int32 TileY = 0;
		BackpackComponent->IndexToTile(Item.Value, TileX, TileY);

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

bool UMSGridWidget::IsPayloadAvailable(UMSItemData* Payload) const
{
	if (!Payload || !BackpackComponent)
	{
		return false;
	}

	return BackpackComponent->IsAvailableForNewItem(Payload, DropItemTopLeftTile);
}

void UMSGridWidget::OnItemRemoved(UMSItemData* TargetItemData)
{
	if (BackpackComponent)
	{
		BackpackComponent->RemoveItem(TargetItemData);
	}
}