// Fill out your copyright notice in the Description page of Project Settings.


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
	

	AActor* PreviousRoom = FirstDungeon;
	
	int MaxRetries = 10; 
	for (int i = 1 ; i < DungeonNumber ; i++)
	{
		if (!PreviousRoom)
		{
			break;
		}
		AMasterRoom* PreviousMasterRoom = Cast<AMasterRoom>(PreviousRoom);
		if (PreviousMasterRoom)
		{
			FVector NextLoc = PreviousMasterRoom->GetRandDirection();
			
			if (PreviousMasterRoom->GetRandDirection() == FVector::ZeroVector)
			{
				i--; 
				RoomList[i-2] = PreviousRoom;
				PreviousMasterRoom = Cast<AMasterRoom>(PreviousRoom);
				NextLoc = PreviousMasterRoom->GetRandDirection();
				// Resuffle here. Get Rand Direction cannot suffle.
				if (PreviousMasterRoom->GetRandDirection() != FVector::ZeroVector)
				{
					// Temporary Copy and Paste 
					NextLoc += PreviousRoom->GetActorLocation();
					AActor* NewRoom = GetWorld()->SpawnActor<AActor>(SpwnDungeon, NextLoc, Rot, SpawnParams);
					RoomList.Add(NewRoom);
					FVector MidPoint = (PreviousRoom->GetActorLocation() + NewRoom->GetActorLocation()) / 2;
					// Spawn the bridge at the midpoint
					GetWorld()->SpawnActor<ABridge>(MidPoint, Rot, SpawnParams);
					UE_LOG(LogTemp, Display, TEXT("NewRoom %i"), i);
					PreviousRoom = NewRoom;
					
				}
			}
			else
			{
				NextLoc += PreviousRoom->GetActorLocation();
				AActor* NewRoom = GetWorld()->SpawnActor<AActor>(SpwnDungeon, NextLoc, Rot, SpawnParams);
				RoomList.Add(NewRoom);
				FVector MidPoint = (PreviousRoom->GetActorLocation() + NewRoom->GetActorLocation()) / 2;
				// Spawn the bridge at the midpoint
				GetWorld()->SpawnActor<ABridge>(MidPoint, Rot, SpawnParams);
				UE_LOG(LogTemp, Display, TEXT("NewRoom %i"), i);
				PreviousRoom = NewRoom;
				
			}
			
			// Calculate the midpoint between the previous room and the new room
		}
	}
	
	
	UE_LOG(LogTemp, Display, TEXT("Dungeon Generated; Try : %i:)"), GenerateCounter);
	GenerateCounter = 0; 
}

void AMasterDungeon::DeleteDungeon()
{
	// must delete all of actors in the world. 
	TArray<AActor*> ActorsToDelete;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMasterRoom::StaticClass(), ActorsToDelete);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABridge::StaticClass(), ActorsToDelete);

	for (AActor* Actor : ActorsToDelete)
	{
		Actor->Destroy();
	}
	
} 


// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	Super::BeginPlay();
	SpawnDungeon();

}





