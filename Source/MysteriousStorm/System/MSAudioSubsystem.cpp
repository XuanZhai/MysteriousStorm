// Fill out your copyright notice in the Description page of Project Settings.


#include "MSAudioSubsystem.h"
#include "MSAudioTableRow.h"
#include "MSDataTableSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UMSAudioSubsystem::PlayAudioAt(int32 ItemID, EAudioType AudioType, FVector Location)
{
	UMSDataTableSubsystem* DataTableSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMSDataTableSubsystem>();
	FMSAudioTableRow AudioRow;
	if(DataTableSubsystem->TryGetAudioByIDWithType(ItemID, AudioType,AudioRow))
	{
		USoundBase* Sound = AudioRow.Sound;
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, Location);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Audio not found"));
	}
	
}

void UMSAudioSubsystem::Play2DAudio(int32 ItemID, EAudioType AudioType)
{
	UMSDataTableSubsystem* DataTableSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UMSDataTableSubsystem>();
	FMSAudioTableRow AudioRow;
	if(DataTableSubsystem->TryGetAudioByIDWithType(ItemID, AudioType,AudioRow))
	{
		USoundBase* Sound = AudioRow.Sound;
		UGameplayStatics::PlaySound2D(GetWorld(), Sound);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("2D Audio not found"));
	}
}
