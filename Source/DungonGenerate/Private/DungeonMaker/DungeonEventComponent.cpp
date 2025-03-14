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
}

void UDungeonEventComponent::AddEvent(TArray<FString> EventName)
{
	int32 i = FMath::RandRange(0, EventName.Num() - 1);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *EventNames[i]);
	// using Case. 
}



