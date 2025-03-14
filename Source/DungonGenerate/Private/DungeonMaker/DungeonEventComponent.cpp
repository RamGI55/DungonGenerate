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
	// Get a random event name
	int Rnd = FMath::RandRange(0, 1000);
	if (Rnd < 700)
	{
		EventName = EventNames[0];
	}
	else if (700 <= Rnd && Rnd  < 750)
	{
		EventName = EventNames[1];
	}
	else if (750 <= Rnd && Rnd <=870)
	{
		EventName = EventNames[2];
	}
	else if (870 <Rnd && Rnd <= 900)
	{
		EventName = EventNames[3];
	}
	else
	{
		EventName = EventNames[4];
	}
	
	//int32 i = FMath::RandRange(0, EventNames.Num() - 1);
//	EventName = EventNames[i];
	UE_LOG(LogTemp, Display, TEXT("EventName %s"), *EventName);
	UE_LOG(LogTemp, Display, TEXT("EventName %i"), Rnd);
	
	// using Case.
}



