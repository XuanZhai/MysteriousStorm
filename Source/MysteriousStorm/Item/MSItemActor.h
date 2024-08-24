// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSItemActor.generated.h"

class UMSItemData;

UENUM(BlueprintType)
enum EItemType : uint8
{
	Item = 0,
	Weapon = 1,
	MAX
};

UCLASS()
class MYSTERIOUSSTORM_API AMSItemActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EItemType> ItemType;

	FVector Location;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;
	
public:	
	UPROPERTY()
	UMSItemData* ItemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitItemData();

public:	
	// Sets default values for this actor's properties
	AMSItemActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UMSItemData* GetItemData() const {return ItemData; }

	bool IsWeapon() const {return ItemType == EItemType::Weapon;}
};
