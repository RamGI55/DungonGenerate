// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterRoom.h"


// Sets default values
AMasterRoom::AMasterRoom()
{
	

<<<<<<< HEAD
	// Direction Arrow 배열 정리. 
	DirectionArrows.Add(NorthExit);
	DirectionArrows.Add(SouthExit);
	DirectionArrows.Add(WestExit);
	DirectionArrows.Add(EastExit);
	
}

const UArrowComponent* AMasterRoom::GetRandDirection()
{
	
	int32 i = FMath::RandRange(0, DirectionArrows.Num() - 1);
	return RandDirection = DirectionArrows[i];
	// has range problem in the Rand integer. 
}

void AMasterRoom::BeginPlay()
{
	Super::BeginPlay();
	GenerateRoom(); 
}

void AMasterRoom::GenerateRoom()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> MasterRoomBP(TEXT("Blueprint'/Game/DungeonMaker/MasterRoom.MasterRoom'"));
	if (MasterRoomBP.Succeeded())
	{
		SpwnDungeon = (UClass*)MasterRoomBP.Object->GeneratedClass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find MasterRoom blueprint"));
	}
	if (SpwnDungeon)
	{
		FActorSpawnParameters SpawnParameters;
		FVector Loc = GetActorLocation();
		FRotator Rot = GetActorRotation();

		AActor* NewRoom = GetWorld()->SpawnActor<AActor>(SpwnDungeon, Loc, Rot, SpawnParameters);
		if (NewRoom)
		{
			UE_LOG(LogTemp, Log, TEXT("Room generated successfully at %s"), *Loc.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to generate room"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SpwnDungeon is not valid"));
	}
=======
>>>>>>> parent of 32952e2 (Random Genertation)
}



