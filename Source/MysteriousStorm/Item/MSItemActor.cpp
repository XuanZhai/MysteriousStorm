// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemActor.h"
#include "MysteriousStorm/System/MSDataTableSubsystem.h"
#include "MysteriousStorm/System/MSItemTableRow.h"
#include "MysteriousStorm/System/MSGameState.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MSItemData.h"

// Sets default values
AMSItemActor::AMSItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	NewRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SetRootComponent(NewRootComponent);
	StaticMeshComp->AttachToComponent(NewRootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	FakeStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FakeStaticMeshComponent"));
	FakeStaticMeshComp->AttachToComponent(NewRootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FakeStaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ItemID = 0;
}

void AMSItemActor::InitItemData()
{
	ItemData = NewObject<UMSItemData>();
	FillItemData();
}

void AMSItemActor::FillItemData()
{
	UGameInstance* GameInstance = GetGameInstance();
	UMSDataTableSubsystem* TableSubsystem = GameInstance->GetSubsystem<UMSDataTableSubsystem>();

	if (!TableSubsystem)
	{
		return;
	}

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
		ItemData->Description = Row.Description;
	}
}

// Called when the game starts or when spawned
void AMSItemActor::BeginPlay()
{
	Super::BeginPlay();

	InitItemData();

	CreateFakeMaterial();

}

// Called every frame
void AMSItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ItemData && ItemData->IsWeapon())
	{
		return;
	}

	if (!GS)
	{
		AGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGameModeBase>();
		GS = GameMode ? Cast<AMSGameState>(GameMode->GetGameState<AMSGameState>()) : nullptr;
	}

	if (GS && !GS->GetIsGamePaused())
	{
		FRotator NewRotation = GetActorRotation() + FRotator(0.0f, 100.0f, 0.0f) * DeltaTime;
		SetActorRotation(NewRotation);
	}
}

