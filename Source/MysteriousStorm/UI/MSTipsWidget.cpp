// Fill out your copyright notice in the Description page of Project Settings.


#include "MSTipsWidget.h"
#include "Components/TextBlock.h"

void UMSTipsWidget::ShowTips(FString Info)
{
	if (bIsVisible || GetWorld()->GetTimerManager().IsTimerActive(DelayHandle))
	{
		HideTips();
	}

	TextInfo = Info;
	GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &UMSTipsWidget::ShowTipsInternal, 0.3f, false);
}

void UMSTipsWidget::ShowTipsInternal()
{
	TXT_Block->SetText(FText::FromString(TextInfo));
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	bIsVisible = true;
}

void UMSTipsWidget::HideTips()
{
	GetWorld()->GetTimerManager().ClearTimer(DelayHandle);
	SetVisibility(ESlateVisibility::Collapsed);
	TXT_Block->SetText(FText::FromString(""));
	bIsVisible = false;
}