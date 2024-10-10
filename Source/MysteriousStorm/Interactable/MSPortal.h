// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSInteractableActor.h"
#include "MSPortal.generated.h"

/**
 * 
 */
UCLASS()
class MYSTERIOUSSTORM_API AMSPortal : public AMSInteractableActor
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector DestWorldLocation;

protected:
	virtual void BeginOverlapCallback() override;

	virtual void EndOverlapCallback() override;
};
