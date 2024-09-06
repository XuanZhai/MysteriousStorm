// Fill out your copyright notice in the Description page of Project Settings.


#include "MSItemData.h"

UMSItemData::UMSItemData()
{
	ID = 0;
	XUISize = 0;
	YUISize = 0;
} 

void UMSItemData::AddEffect(EMSEffect NewEffect)
{
	UE_LOG(LogTemp, Warning, TEXT("%s add effect"), *Name);
	Effects.Add(NewEffect);
}

void UMSItemData::RemoveEffect(EMSEffect TargetEffect) 
{ 
	UE_LOG(LogTemp, Warning, TEXT("%s remove effect"), *Name); 
	Effects.Remove(TargetEffect);
}