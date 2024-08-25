// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSGridWidget.generated.h"

class UCanvasPanel;
class UBorder;
class UMSItemWidget;
class UMSItemData;
class UMSBackpackComponent;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSGridWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* GridPanel;

	UPROPERTY(BlueprintReadWrite)
	UMSBackpackComponent* BackpackComponent;

	UPROPERTY(BlueprintReadWrite)
	float TileSize = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMSItemWidget> ItemWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DropItemTopLeftTile = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDrawDropLocation = false;

public:
	UFUNCTION(BlueprintCallable)
	void Refresh();

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void CreateLineSegment();

	UFUNCTION(BlueprintCallable)
	void Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent);

	UFUNCTION(BlueprintCallable)
	bool IsPayloadAvailable(UMSItemData* Payload) const;

	UFUNCTION()
	void OnItemRemoved(UMSItemData* TargetItemData);
};
