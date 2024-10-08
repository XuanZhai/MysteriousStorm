// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSGridWidget.h"
#include "MSStorageWidget.generated.h"

class UMSBackpackWidget;
class UCanvasPanel;
class UBorder;
class UMSItemWidget;
class UMSItemData;
class UMSBackpackComponent;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSStorageWidget : public UMSGridWidget
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UBorder* GridBorder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* GridPanel;

public:
	UFUNCTION(BlueprintCallable)
	void Initialization(float NewTileSize, UMSBackpackComponent* NewBackpackComponent);

	UFUNCTION(BlueprintCallable)
	void Refresh();

};
