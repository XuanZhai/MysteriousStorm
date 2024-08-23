// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemActor.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSItemTableRow.h"

// Sets default values
AMSItemActor::AMSItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMSItemActor::InitStaticMesh()
{

}

// Called when the game starts or when spawned
void AMSItemActor::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = GetGameInstance();
	UMSDataTableSubsystem* TableSubsystem = GameInstance->GetSubsystem<UMSDataTableSubsystem>();
	
	if (TableSubsystem)
	{
		TableSubsystem->OnTableLoaded.AddUniqueDynamic(this, &AMSItemActor::InitItemDataFromTable);
	}
}

void AMSItemActor::InitItemDataFromTable(UMSDataTableSubsystem* DataTableSubsystem)
{
	if (!DataTableSubsystem)
	{
		return;
	}

	FMSItemTableRow Row;
	if (DataTableSubsystem->TryGetRowByItemID(ItemData.ItemID, Row))
	{
		ItemData.UIPath = Row.UIPath;
		ItemData.PreviewUIPath = Row.PreviewUIPath;
	}
}

// Called every frame
void AMSItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

