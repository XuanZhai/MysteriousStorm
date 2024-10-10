
// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemData.h"

UMSItemData::UMSItemData()
{
	ID = 0;
	XUISize = 0;
	YUISize = 0;
} 

void UMSItemData::AddEffect(EMSEffect NewEffect, int32 Level)
{
	UE_LOG(LogTemp, Warning, TEXT("%s add effect"), *Name);
	Effects.Add(NewEffect, Level);
}

void UMSItemData::RemoveEffect(EMSEffect TargetEffect) 
{ 
	UE_LOG(LogTemp, Warning, TEXT("%s remove effect"), *Name); 
	Effects.Remove(TargetEffect);
}

void UMSItemData::ClearEffect()
{
	Effects.Empty();
}