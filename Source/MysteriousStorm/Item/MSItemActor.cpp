// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemActor.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSItemTableRow.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MSItemData.h"

// Sets default values
AMSItemActor::AMSItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ItemID = 0;
}

void AMSItemActor::InitItemData()
{
	UGameInstance* GameInstance = GetGameInstance();
	UMSDataTableSubsystem* TableSubsystem = GameInstance->GetSubsystem<UMSDataTableSubsystem>();

	if (!TableSubsystem)
	{
		return;
	}

	ItemData = NewObject<UMSItemData>();
	FMSItemTableRow Row;
	if (ItemData && TableSubsystem->TryGetRowByItemID(ItemID, Row))
	{
		


		ItemData->ID = Row.ID;
		ItemData->Name = Row.Name;
		ItemData->ItemType = Row.ItemType;
		ItemData->UIPath = Row.UIPath;
		ItemData->XUISize = Row.XUISize;
		ItemData->YUISize = Row.YUISize;
		ItemData->AssetBP = Row.AssetBP;
	}
}

// Called when the game starts or when spawned
void AMSItemActor::BeginPlay()
{
	Super::BeginPlay();

	InitItemData();
}

// Called every frame
void AMSItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

