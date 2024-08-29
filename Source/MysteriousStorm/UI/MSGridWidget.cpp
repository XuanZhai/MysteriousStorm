// Fill out your copyright notice in the Description page of Project Settings.


#include "MSGridWidget.h"
#include "MysteriousStorm/Item/MSItemData.h"

void UMSGridWidget::IndexToTile(const int32 InIndex, int32& OutX, int32& OutY, const int32 ColumnNum) const
{
	OutX = InIndex % ColumnNum;
	OutY = InIndex / ColumnNum; 
}

void UMSGridWidget::TileToIndex(const int32 InX, const int32 InY, int32& OutIndex, const int32 ColumnNum) const
{
	OutIndex = InX + InY * ColumnNum;
}

bool UMSGridWidget::IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex, const TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart, ColNum);

	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	if (TileXStart < 0 || TileYStart < 0) return false;
	if (TileXEnd > ColNum || TileYEnd > RowNum) return false;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex, ColNum);

			if (!InTiles.IsValidIndex(CurrentIndex))
			{
				return false;
			}
			else if (InTiles[CurrentIndex] != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

void UMSGridWidget::FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex, TArray<UMSItemData*>& InTiles, const int32 ColNum) const
{
	int32 TileXStart = 0;
	int32 TileYStart = 0;
	IndexToTile(TopLeftIndex, TileXStart, TileYStart, ColNum);
	int32 TileXEnd = TileXStart + NewItemData->XUISize;
	int32 TileYEnd = TileYStart + NewItemData->YUISize;

	for (int32 x = TileXStart; x < TileXEnd; x++)
	{
		for (int32 y = TileYStart; y < TileYEnd; y++)
		{
			int32 CurrentIndex = 0;
			TileToIndex(x, y, CurrentIndex, ColNum);

			if (InTiles.IsValidIndex(CurrentIndex))
			{
				InTiles[CurrentIndex] = NewItemData;
			}
		}
	}
}
