// Fill out your copyright notice in the Description page of Project Settings.


#include "MSPortal.h"

void AMSPortal::BeginOverlapCallback()
{
	if (InteractingCharacter)
	{
		InteractingCharacter->SetActorLocation(DestWorldLocation);
	}
}

void AMSPortal::EndOverlapCallback()
{

}