// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MSDataTableSubsystem.generated.h"

class UDataTable;
struct FStreamableHandle;
/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSDataTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<FStreamableHandle> StreamableHandle;

	FSoftObjectPath ItemTablePath{ "/Game/Tables/DT_ItemData.DT_ItemData" };
	FSoftObjectPath WeaponTablePath{ "/Game/Tables/DT_WeaponData.DT_WeaponData" };
	
	UPROPERTY()
	UDataTable* ItemTable;

	UPROPERTY()
	UDataTable* WeaponTable;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTableLoaded, UMSDataTableSubsystem*, DataTableSubsystem);
	UPROPERTY(BlueprintAssignable)
	FOnTableLoaded OnTableLoaded;

protected:
	// Called when the subsystem is initialized
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void OnDataTableLoaded();

	// Called when the subsystem is deinitialized
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	UDataTable* GetItemTable() const { return ItemTable; }

	bool TryGetRowByItemID(const int32 ItemID, struct FMSItemTableRow& OutRow) const;

	bool TryGetWeaponConfigByItemID(const int32 ItemID, struct FMSWeaponTableRow& OutRow) const;

	UFUNCTION(BlueprintCallable)
	UDataTable* GetWeaponTable() const { return WeaponTable; }
};
