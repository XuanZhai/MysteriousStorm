// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSInteractableActor.h"
#include "MSStorageBox.generated.h"

class UMSItemData;
/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSStorageBox : public AMSInteractableActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UMSItemData*> StorageList;

protected:
	virtual void BeginOverlapCallback() override;

	virtual void EndOverlapCallback() override;
};
