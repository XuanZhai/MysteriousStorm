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
	TMap<UMSItemData*, int32> Items;

	UPROPERTY(BlueprintReadWrite)
	TArray<UMSItemData*> WeaponList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UMSItemData*> Tiles;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

#pragma region CachedPickUpList
protected:
	UPROPERTY(BlueprintReadWrite)
	TMap<UMSItemData*, int32> CachedItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray <UMSItemData*> CachedTiles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UMSItemData*, AMSItemActor*> CachedPickUpList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CachedRowNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CachedColumnNumber;

public:
	UFUNCTION(BlueprintCallable)
	void AddToCachedPickUpList(AMSItemActor* NewItem);

	UFUNCTION(BlueprintCallable)
	void RemoveFromCachedPickUpList(AMSItemActor* TargetItem);

	UFUNCTION(BlueprintCallable)
	const TMap<UMSItemData*, AMSItemActor*>& GetCachedPickUpList() const { return CachedPickUpList; }

	void ClearCachedPickUpList();

	UFUNCTION(BlueprintCallable)
	bool TryFillCachedTiles();

	UFUNCTION(BlueprintCallable)
	const TMap<UMSItemData*, int32>& GetCachedItems() const { return CachedItems; }
#pragma endregion

#pragma region Backpack
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RowNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ColumnNumber;

protected:
	void FillTilesWithItem(UMSItemData* NewItemData, int32 TopLeftIndex, TArray<UMSItemData*>& InTiles, const int32 ColNum);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBackpackChanged);
	UPROPERTY(BlueprintAssignable)
	FOnBackpackChanged OnBackpackChanged;

	UPROPERTY()
	bool NeedRefresh;

	UFUNCTION(BlueprintCallable)
	void OpenBackpack();

	UFUNCTION(BlueprintCallable)
	void CloseBackpack();

	UFUNCTION(BlueprintCallable)
	void IndexToTile(const int32 InIndex, int32& OutX, int32& OutY, const int32 ColumnNum) const;

	UFUNCTION(BlueprintCallable)
	void TileToIndex(const int32 InX, const int32 InY, int32& OutIndex, const int32 ColumnNum) const;

	UFUNCTION(BlueprintCallable)
	bool IsAvailableForNewItem(const UMSItemData* NewItemData, int32 TopLeftIndex, const TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum) const;

	UFUNCTION(BlueprintCallable)
	bool CanAddThisItem(UMSItemData* NewItemData, bool bIsBackpack) const;

	UFUNCTION(BlueprintCallable)
	bool TryAddThisItem(UMSItemData* NewItemData, UPARAM(ref) TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum);

	UFUNCTION(BlueprintCallable)
	void AddThisItemAt(UMSItemData* NewItemData, int32 TopLeftIndex, UPARAM(ref) TArray<UMSItemData*>& InTiles, int32 ColNum, int32 RowNum);

	UFUNCTION(BlueprintCallable)
	const TMap<UMSItemData*, int32>& GetItems() const { return Items; }

	UFUNCTION(BlueprintCallable)
	void RemoveItem(UMSItemData* TargetItem, bool bIsBackpack);
#pragma endregion
};
