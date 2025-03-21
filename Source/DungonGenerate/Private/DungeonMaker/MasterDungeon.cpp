// Fill out your copyright notice in the Description page of Project Settings.

// Version 2 Edition - 03. 21. 2025 2:00PM 

#include "DungeonMaker/MasterDungeon.h"

#include "DungeonMaker/Bridge.h"
#include "DungeonMaker/MasterRoom.h" 
#include "Kismet/GameplayStatics.h"


// Sets default values
AMasterDungeon::AMasterDungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DungeonNumber = 10;
	GenerateCounter = 0; 
	
}

void AMasterDungeon::SpawnDungeon() 
{ 
	FActorSpawnParameters SpawnParameters;
    FRotator Rot(0, 0, 0);
    FVector Loc(0, 0, 0);
	
    SpnMasterDungeon = LoadObject<UBlueprint>(
    	nullptr, TEXT("/Script/Engine.Blueprint'/Game/DungeonMaker/BPMainRoom.BPMainRoom'"));
    SpwnDungeon = (UClass*)SpnMasterDungeon->GeneratedClass;
    FActorSpawnParameters SpawnParams;
	FirstDungeon = GetWorld()->SpawnActor<AActor>(SpwnDungeon, Loc, Rot, SpawnParameters);
	

	AActor* CurrentRoom = FirstDungeon;
	
	for (int i = 1 ; i < DungeonNumber ; i++)
	{
		if (!CurrentRoom)
		{
			break;
		}
		
		AMasterRoom* CurrentMasterRoom = Cast<AMasterRoom>(CurrentRoom);
		if (CurrentMasterRoom)
		{
			// back to the previous room if the has now direction to go. 
			for (int j = i - 2; CurrentMasterRoom->GetRandDirection() == FVector::ZeroVector && j >= 0; --j)
			{
				CurrentRoom = RoomList[j];
				CurrentMasterRoom = Cast<AMasterRoom>(CurrentRoom);
			}
			
			FVector NextLoc = CurrentMasterRoom->GetRandDirection();
			NextLoc += CurrentRoom->GetActorLocation();
			AActor* NewRoom = GetWorld()->SpawnActor<AActor>(SpwnDungeon, NextLoc, Rot, SpawnParams);

			RoomList.Add(NewRoom);
			/*
			FVector MidPoint = (CurrentRoom->GetActorLocation() + NewRoom->GetActorLocation()) / 2;
			// Spawn the bridge at the midpoint

			
			GetWorld()->SpawnActor<ABridge>(MidPoint, Rot, SpawnParams);
			UE_LOG(LogTemp, Display, TEXT("NewRoom %i"), i);
			*/
			CurrentRoom = NewRoom;
			
			
			// Calculate the midpoint between the previous room and the new room
		}
	}
	/*
	for (int i = 1 ; i < DungeonNumber - 1 ;i++)
	{
		if (!RoomList.IsValidIndex(i))
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid RoomList index: %d (Size: %d)"), i, RoomList.Num());
			continue;
		}
		CurrentRoom = RoomList[i];
		AMasterRoom* CurrentMasterRoom = Cast<AMasterRoom>(CurrentRoom);
		TArray<FVector> RouteDirection;
		if (CurrentMasterRoom->GetRouteDirection().Num() >= 1)
		{
			for (int j = 1; j < CurrentMasterRoom->GetRouteDirection().Num(); j++)
			{
				if (!CurrentMasterRoom) 
				{
					UE_LOG(LogTemp, Error, TEXT("CurrentMasterRoom is nullptr at index %d"), i);
					continue;
				}
				FVector MidPoint = (CurrentRoom->GetActorLocation() + CurrentMasterRoom->GetRouteDirection()[i]/2);
				RouteDirection.Add(MidPoint);
				if (CurrentMasterRoom->GetRouteDirection().IsValidIndex(j))
				{
					GetWorld()->SpawnActor<ABridge>(MidPoint, Rot, SpawnParams);
				}
			}
		}
		
	}
	*/
	UE_LOG(LogTemp, Display, TEXT("Dungeon Generated; Try : %i:)"), GenerateCounter);
	GenerateCounter = 0; 
}

// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	Super::BeginPlay();
	SpawnDungeon();

}


