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
			CurrentRoom = NewRoom;

			// if the collision isn't detected remove the bridge mesh. 
			
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Dungeon Generated; Try : %i:)"), GenerateCounter);
	GenerateCounter = 0; 
}

// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	Super::BeginPlay();
	SpawnDungeon();

}


