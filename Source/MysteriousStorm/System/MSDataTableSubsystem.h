// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MSDataTableSubsystem.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSDataTableSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> ItemTableRef;

	UPROPERTY()
	UDataTable* ItemTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UDataTable> WeaponTableRef;

	UPROPERTY()
	UDataTable* WeaponTable;

protected:
	// Called when the subsystem is initialized
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Called when the subsystem is deinitialized
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable)
	UDataTable* GetItemTable() const { return ItemTable; }

	UFUNCTION(BlueprintCallable)
	bool TryGetAssetPathByItemID(const int32 ItemID, FSoftObjectPath& OutObjectPath);

	UFUNCTION(BlueprintCallable)
	UDataTable* GetWeaponTable() const { return WeaponTable; }
};
