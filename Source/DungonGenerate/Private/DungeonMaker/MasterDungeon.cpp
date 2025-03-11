// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterDungeon.h"
#include "DungeonMaker/MasterRoom.h"

// Sets default values
AMasterDungeon::AMasterDungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

TSubclassOf<class UObject> AMasterDungeon::GetBPDungeon()
{
	TObjectPtr<UBlueprint> SpnMasterDungeon = LoadObject<UBlueprint>(nullptr, TEXT ("/Script/Engine.Blueprint'/Game/DungeonMaker/MasterRoom.MasterRoom'"));
	SpwnDungeon = (UClass*)SpnMasterDungeon->GeneratedClass;
	return SpwnDungeon; 
}

void AMasterDungeon::GetTheInitialDungeon()
{
	Super::BeginPlay();
	FActorSpawnParameters SpawnParameters;
	FRotator Rot(0,0,0);
	FVector Loc(0,0,0); 

	GetBPDungeon(); 
	//SpnMasterDungeon = LoadObject<UBlueprint>(nullptr, TEXT ("/Script/Engine.Blueprint'/Game/DungeonMaker/MasterRoom.MasterRoom'"));
	//TSubclassOf<class UObject> SpwnDungeon = (UClass*)SpnMasterDungeon->GeneratedClass;
	GetWorld()->SpawnActor<AActor>(SpwnDungeon, Loc, Rot); 
}

void AMasterDungeon::GetNextRoom()
{
	MasterRoom->GetRandDirection();
	TObjectPtr<UBlueprint> SpnDungeon;
	GetBPDungeon();
	FVector NewLoc = MasterRoom->GetRandDirection()->GetComponentLocation();
	FRotator NewRot = MasterRoom->GetRandDirection()->GetComponentRotation(); 
	GetWorld()->SpawnActor<AActor>(SpwnDungeon, NewLoc,
								   NewRot);
} 
// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	GetTheInitialDungeon();
	GetNextRoom();
}


