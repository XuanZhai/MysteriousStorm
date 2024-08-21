// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MysteriousStorm/Item/MSItemData.h"
#include "MSBackpackComponent.generated.h"

class AMSItemActor;

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

	// TODO: Be used to store the weapon in the bags. May be changed later. [ZX]
	TArray<FMSItemData> WeaponBags;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool CanPickUpThisItem(AMSItemActor* NewItem) const;

	UFUNCTION(BlueprintCallable)
	bool TryPickUpThisItem(AMSItemActor* NewItem);


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
};
