// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MSItemData.generated.h"

class AMSItemActor;
enum EMSEffect : uint8;

UENUM(BlueprintType)
enum EItemType : uint8
{
	Item = 0,
	Weapon = 1,
	Bag = 2,
	MAX
};

/**
 * 
 */
UCLASS(Blueprintable)
class MYSTERIOUSSTORM_API UMSItemData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EItemType> ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 XUISize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 YUISize;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	FSoftObjectPath UIPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMSItemActor> AssetBP; 

	UPROPERTY(BlueprintReadWrite)
	float RotateDegree;

public:
	UMSItemData();

	bool IsWeapon() const { return ItemType == EItemType::Weapon; }

	bool IsBag() const { return ItemType == EItemType::Bag; }

	virtual void AddEffect(EMSEffect NewEffect) { UE_LOG(LogTemp, Warning, TEXT("%s add effect"), *Name); };

	virtual void RemoveEffect(EMSEffect TargetEffect) { UE_LOG(LogTemp, Warning, TEXT("%s remove effect"), *Name); };
};
