// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSGridWidget.generated.h"

class UMSItemData;

UENUM(BlueprintType)
enum EGridType : uint8
{
	CachedGrid = 0 UMETA(DisplayName = "CachedGrid"),
	BackpackGrid = 1 UMETA(DisplayName = "BackpackGrid"),
};

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintCallable)
	void IndexToTile(const int32 InIndex, int32& OutX, int32& OutY, const int32 ColumnNum) const;

	UFUNCTION(BlueprintCallable)
	void TileToIndex(const int32 InX, const int32 InY, int32& OutIndex, const int32 ColumnNum) const;

	UFUNCTION(BlueprintCallable)
	bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex, const TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum) const;

	void FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex, TArray<UMSItemData*>& InTiles, const int32 ColNum) const;
};
