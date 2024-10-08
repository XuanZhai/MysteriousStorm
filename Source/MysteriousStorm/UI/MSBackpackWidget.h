// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "MSBackpackWidget.generated.h"


class UMSBackpackComponent;
class UMSItemData;
class UMSCachedGridWidget;
class UMSBackpackGridWidget;
class UMSStorageWidget;
class AMSStorageBox;

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSBackpackWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMSCachedGridWidget* WB_CachedGridWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMSBackpackGridWidget* WB_GridWidget;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UMSStorageWidget* WB_StorageGridWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMSBackpackComponent* BackpackComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TileSize = 0.0f;

protected:
	virtual bool NativeOnDrop( const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation );

	UFUNCTION(BlueprintCallable)
	void InitializeGrid();

	UFUNCTION()
	void OnMouseDroppedCallback();
#pragma endregion

protected:
	UFUNCTION()
	void EnterStorageBox(AMSStorageBox* NewBox);

	UFUNCTION()
	void LeaveStorageBox(AMSStorageBox* OldBox);
};
