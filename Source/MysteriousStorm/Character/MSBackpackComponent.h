// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MSBackpackComponent.generated.h"

class AMSItemActor;
class UMSItemData;

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent) )
class MYSTERIOUSSTORM_API UMSBackpackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMSBackpackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
 	TArray<UMSItemData*> Items;

	UPROPERTY(BlueprintReadWrite)
	TArray<UMSItemData*> Weapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMSItemData*> Tiles;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region CachedPickUpList
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AMSItemActor*> CachedPickUpList;

public:
	UFUNCTION(BlueprintCallable)
	void AddToCachedPickUpList(AMSItemActor* NewItem);

	UFUNCTION(BlueprintCallable)
	void RemoveFromCachedPickUpList(AMSItemActor* TargetItem);

	UFUNCTION(BlueprintCallable)
	TArray<AMSItemActor*>& GetCachedPickUpList() { return CachedPickUpList; }
#pragma endregion

#pragma region Backpack
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RowNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ColumnNumber;

protected:
	bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex) const;

	void FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex);

public:
	void IndexToTile(const int32 InIndex, int32& OutX, int32& OutY) const;

	UFUNCTION(BlueprintCallable)
	bool CanPickUpThisItem(AMSItemActor* NewItem) const;

	UFUNCTION(BlueprintCallable)
	bool TryPickUpThisItem(AMSItemActor* NewItem);
#pragma endregion
};
