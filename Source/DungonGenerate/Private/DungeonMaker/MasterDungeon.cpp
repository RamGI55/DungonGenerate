// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterDungeon.h"





// Sets default values
AMasterDungeon::AMasterDungeon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

<<<<<<< HEAD
AActor* AMasterDungeon::GetMasterDungeon()
{
	return MasterRoom; 
}

void AMasterDungeon::GetTheInitialDungeon()
{
	FActorSpawnParameters SpawnParameters;
	FRotator Rot(0, 0, 0);
	FVector Loc(0, 0, 0);
	MasterRoom = GetWorld()->SpawnActor<AMasterRoom>(AMasterRoom::StaticClass(), Loc, Rot, SpawnParameters); 
	if (MasterRoom)
	{
		MasterRoom->GenerateRoom(); 
	}
}

void AMasterDungeon::GetNextRoom()
{
	MasterRoom->GetRandDirection();
	TObjectPtr<UBlueprint> SpnDungeon;
	GetMasterDungeon();
	FVector NewLoc = MasterRoom->GetRandDirection()->GetComponentLocation();
	FRotator NewRot = MasterRoom->GetRandDirection()->GetComponentRotation(); 

} 
// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{	
	GetTheInitialDungeon();

=======
// Called when the game starts or when spawned
void AMasterDungeon::BeginPlay()
{
	FActorSpawnParameters SpawnParameters;
	FRotator Rot(0,0,0);
	FVector Loc(0,0,0); 
	Super::BeginPlay();

	SpnMasterDungeon = LoadObject<UBlueprint>(nullptr, TEXT ("/Script/Engine.Blueprint'/Game/DungeonMaker/MasterRoom.MasterRoom'"));
	TSubclassOf<class UObject> SpwnDungeon = (UClass*)SpnMasterDungeon->GeneratedClass;
	GetWorld()->SpawnActor<AActor>(SpwnDungeon, Loc, Rot); 
	
>>>>>>> parent of 32952e2 (Random Genertation)
}


