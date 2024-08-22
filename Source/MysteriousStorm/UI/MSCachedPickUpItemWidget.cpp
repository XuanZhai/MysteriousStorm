// Fill out your copyright notice in the Description page of Project Settings.


#include "MSCachedPickUpItemWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMSCachedPickUpItemWidget::SetItemName(const FString& NewItemName)
{
	if (ItemName)
	{
		ItemName->SetText(FText::AsCultureInvariant(NewItemName));
	}
}

void UMSCachedPickUpItemWidget::SetItemImage(const FSoftObjectPath& UIPath)
{
	if (ItemImage && UIPath.IsValid())
	{
		UTexture2D* Texture = Cast<UTexture2D>(UIPath.TryLoad());
		ItemImage->SetBrushFromTexture(Texture);
	}
}