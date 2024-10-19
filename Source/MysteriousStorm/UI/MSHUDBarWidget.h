// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MSHUDBarWidget.generated.h"

class UMSBackpackComponent;
class UMSHUDItemWidget;
class UProgressBar;
class UCanvasPanel;
class UMSItemData;

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API UMSHUDBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* Bar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UMSBackpackComponent* BackpackComponent;

	UPROPERTY()
	TMap<UMSHUDItemWidget*, UMSItemData*> Items;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMSHUDItemWidget> ChildWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	float TotalTime = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentTime = 0.0f;

	bool CanTick = true;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void OnOpenBackpack();

	UFUNCTION()
	void OnCloseBackpack();

	void CreateChild(UMSItemData* ItemData);

	void IdentifyChild(float OldValue, float NewValue);
};
