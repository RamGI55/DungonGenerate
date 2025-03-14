// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterDungeon.h"

#include "DungeonMaker/Bridge.h"
#include "DungeonMaker/MasterRoom.h" 


// Sets default values
AMasterDungeon::AMasterDungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DungeonNumber = 10;
	
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

	AActor* PreviousRoom = FirstDungeon;
	for (int i = 1 ; i < DungeonNumber ; i++)
	{
		if (PreviousRoom)
		{
			AMasterRoom* PreviousMasterRoom = Cast<AMasterRoom>(PreviousRoom);
			if (PreviousMasterRoom)
			{
				FVector NextLoc = PreviousMasterRoom->GetRandDirection();
				NextLoc += PreviousRoom->GetActorLocation();
				AActor* NewRoom = GetWorld()->SpawnActor<AActor>(SpwnDungeon, NextLoc, Rot, SpawnParams);

				// Calculate the midpoint between the previous room and the new room
				FVector MidPoint = (PreviousRoom->GetActorLocation() + NewRoom->GetActorLocation()) / 2;
	
				// Spawn the bridge at the midpoint
				GetWorld()->SpawnActor<ABridge>(MidPoint, Rot, SpawnParams);
				UE_LOG(LogTemp, Display, TEXT("NewRoom %i"), i);
				PreviousRoom = NewRoom;
				
			}
		}
	}
}


// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	Super::BeginPlay();
	SpawnDungeon();
	/*
	for (int i = 0; i < DungeonNumber; i++)
	{ 
		if (FirstDungeon)
		{	
			AMasterRoom* FirstRoom = Cast<AMasterRoom>(FirstDungeon);
			if (FirstRoom)
			{
				FRotator Rot(0, 0, 0);
				FVector NextLoc = FirstRoom->GetRandDirection();
				AActor* NewDungeon = GetWorld()->SpawnActor<AActor>(SpwnDungeon, NextLoc, Rot); // Must another TsubClass which has been newly generated. 
				if (NewDungeon)
				{
					FirstDungeon = NewDungeon;
				}
			}
		}
		
	}
	*/
}





