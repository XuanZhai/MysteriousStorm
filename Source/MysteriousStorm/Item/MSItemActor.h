// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSItemData.h"
#include "MSItemActor.generated.h"

struct FMSItemData;

UCLASS()
class MYSTERIOUSSTORM_API AMSItemActor : public AActor
{
	GENERATED_BODY()

protected:
	FMSItemData ItemData;

	enum EWeaponType {  };
	struct FWeapon
	{
		int ConfigId;
		int Count;
		EWeaponType WeaponType;
		// 还有当前武器buff
	};
	
	FVector Location;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshComp;
	
public:	
	// Sets default values for this actor's properties
	AMSItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitStaticMesh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	FMSItemData& GetItemData() { return ItemData; }
};
