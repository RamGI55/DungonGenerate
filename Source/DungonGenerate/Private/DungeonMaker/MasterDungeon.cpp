// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterDungeon.h"

#include "DungeonMaker/MasterRoom.h"


// Sets default values
AMasterDungeon::AMasterDungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMasterDungeon::SpawnDungeon()
{
	FActorSpawnParameters SpawnParameters;
    FRotator Rot(0, 0, 0);
    FVector Loc(0, 0, 0);
    
    
    SpnMasterDungeon = LoadObject<UBlueprint>(
    	nullptr, TEXT("/Script/Engine.Blueprint'/Game/DungeonMaker/BPMasterRoom.BPMasterRoom'"));
    SpwnDungeon = (UClass*)SpnMasterDungeon->GeneratedClass;
    FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName("MyDungeonActor");
	FirstDungeon = GetWorld()->SpawnActor<AActor>(SpwnDungeon, Loc, Rot, SpawnParameters);
}


// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	Super::BeginPlay();
	SpawnDungeon();
	if (FirstDungeon)
	{
		AMasterRoom* FirstRoom = Cast<AMasterRoom>(FirstDungeon);
		if (FirstRoom)
		{
			FRotator Rot(0, 0, 0);
			FVector NextLoc = FirstRoom->GetRandDirection();
			GetWorld()->SpawnActor<AActor>(SpwnDungeon, NextLoc, Rot);
		}
	}
	
	
	

}




