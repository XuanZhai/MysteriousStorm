// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSItemActor.generated.h"

class UMSItemData;

UCLASS()
class MYSTERIOUSSTORM_API AMSItemActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 ItemID;

	FVector Location;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;
	
public:	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* BaseUIMaterial;

	UPROPERTY()
	UMSItemData* ItemData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InitItemData();

public:	
	// Sets default values for this actor's properties
	AMSItemActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	UMSItemData* GetItemData() const {return ItemData; }
};
