// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/DungeonEventComponent.h"


// Sets default values for this component's properties
UDungeonEventComponent::UDungeonEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	EventNames.Add(FString("Enemy"));
	EventNames.Add(FString("Treasure"));
	EventNames.Add(FString("Trap"));
	EventNames.Add(FString("Shop"));
	EventNames.Add(FString("Boss"));
	EventNames.Add(FString("End"));
}

void UDungeonEventComponent::GetEvent()
{
	
	int32 i = FMath::RandRange(0, EventNames.Num() - 1);
	EventName = EventNames[i];
	UE_LOG(LogTemp, Display, TEXT("EventName %s"), *EventName);
	
	// using Case.
}



