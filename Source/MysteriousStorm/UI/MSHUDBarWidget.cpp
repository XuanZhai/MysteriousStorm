// Fill out your copyright notice in the Description page of Project Settings.


#include "MSHUDBarWidget.h"
#include "MysteriousStorm/Character/MSCharacter.h"
#include "MysteriousStorm/Character/MSBackpackComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/ProgressBar.h"
#include "MSHUDItemWidget.h"

void UMSHUDBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AMSCharacter* Character = GetOwningPlayerPawn<AMSCharacter>();
	BackpackComponent = Character ? Character->GetBackpackComponent() : nullptr;
	if (BackpackComponent)
	{
		BackpackComponent->OnBackpackOpened.AddUniqueDynamic(this, &UMSHUDBarWidget::OnOpenBackpack);
		BackpackComponent->OnBackpackClosed.AddUniqueDynamic(this, &UMSHUDBarWidget::OnCloseBackpack);
	}

}

void UMSHUDBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CanTick)
	{
		return;
	}

	float OldTime = CurrentTime;
	CurrentTime += InDeltaTime;

	if (CurrentTime >= TotalTime)
	{
		CurrentTime = 0;
	}

	float NewProgress = CurrentTime / TotalTime;
	Bar->SetPercent(NewProgress);

	IdentifyChild(OldTime, CurrentTime);
}

void UMSHUDBarWidget::OnOpenBackpack()
{
	SetVisibility(ESlateVisibility::Collapsed);
	CanTick = false;
	
	for (const auto& ChildWidget : Items)
	{
		ChildWidget.Key->RemoveFromParent();
	}
	Items.Empty();

	TotalTime = 0.0f;
	CurrentTime = 0.0f;
}

void UMSHUDBarWidget::OnCloseBackpack()
{
	if (!BackpackComponent)
	{
		return;
	}

	const auto& BagItems = BackpackComponent->GetItems();
	if (BagItems.Num() == 0)
	{
		return;
	}

	SetVisibility(ESlateVisibility::HitTestInvisible);
	CanTick = true;

	TotalTime = BackpackComponent->TotalTime;

	for (const auto& Item : BagItems)
	{
		CreateChild(Item.Key);
	}

}

void UMSHUDBarWidget::CreateChild(UMSItemData* ItemData)
{
	if (TotalTime == 0)
	{
		return;
	}

	UUserWidget* NewWidget = CreateWidget(this, ChildWidgetClass);
	UMSHUDItemWidget* ItemWidget = NewWidget ? Cast<UMSHUDItemWidget>(NewWidget) : nullptr;

	if (ItemWidget)
	{
		ItemWidget->SetImage(ItemData->UIPath);
		ItemWidget->SetBackground(0);
		TArray<TEnumAsByte<EMSEffect>> NewEffect;
		ItemWidget->SetEffect(NewEffect);
	}

	auto PanelSlot = CanvasPanel->AddChild(ItemWidget);
	if (UCanvasPanelSlot* CanvasPanelSlot = PanelSlot ? Cast<UCanvasPanelSlot>(PanelSlot) : nullptr)
	{
		CanvasPanelSlot->SetSize(FVector2D(50.0f,50.0f));
		CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		float Position = 1000 * (ItemData->TriggerTimeInRound / TotalTime);
		CanvasPanelSlot->SetPosition(FVector2D(Position, 0.0f));
	}

	Items.Add(ItemWidget,ItemData);
}

void UMSHUDBarWidget::IdentifyChild(float OldValue, float NewValue)
{
	if (NewValue < 0.00001f)
	{
		for (const auto& Item : Items)
		{
			Item.Key->SetBackground(0);
			TArray<TEnumAsByte<EMSEffect>> NewEffect;
			Item.Key->SetEffect(NewEffect);
		}

		return;
	}
	
	for (const auto& Item : Items)
	{
		if (Item.Value->TriggerTimeInRound >= OldValue && Item.Value->TriggerTimeInRound <= NewValue)
		{
			Item.Key->SetBackground(static_cast<int32>(Item.Value->ItemType));

			TArray<TEnumAsByte<EMSEffect>> NewEffect;
			for (const auto& Effect : Item.Value->Effects)
			{
				NewEffect.Add(Effect.Key);
			}
			Item.Key->SetEffect(NewEffect);
		}
	}
}