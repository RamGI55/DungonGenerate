

// This source code is for the portfoilo purpose.

// ---------------------------------------------------- //
// Project Name: Endless Spiral							//
// File Name: DungeonGen.h								//
// Written by: Hyunsoo Park								//
// Edited by:											//
// Generated Date: Mar 07, 2025							//
// Modified Date:										//
// ----------------------------------------------------	//

// DEC : This is the actor class for the random map generation. 


#include "DungeonGen.h"
#include "Engine/StaticMeshActor.h"




void ADungeonGen::BeginPlay()
{
	
	Super::BeginPlay();
	MaxRoomNumber = 15;
	PlacetheRoom();
	GenerateRoom();
}

// Sets default values
ADungeonGen::ADungeonGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	iMinRoomSize = 100;
	iMaxRoomSize = 500;
	iMazeSize = 250000;

}

void ADungeonGen::GetRandomRoom()
{
	// Getter of the size 
	const float RoomWidth = FMath::RandRange(iMinRoomSize, iMaxRoomSize);
	const float RoomHeight = FMath::RandRange(iMinRoomSize, iMaxRoomSize);
	const FVector2D Size(RoomWidth, RoomHeight);
	// Getter 
	RoomSize = Size;

	// Getter of the position 
	const int32 RoomPosXMax = iMazeSize - FMath::TruncToInt(Size.X);
	const int32 RoomPosYMax = iMazeSize - FMath::TruncToInt(Size.Y);
	const int32 x = FMath::RandRange(0, 20000);
	const int32 y = FMath::RandRange(0, 20000);
	const FVector2D Pos (x,y);
	// Getter 
	RoomPosition = Pos;
	
}

void ADungeonGen::PlacetheRoom()
{
	
	for (int32 i = 0 ; i < MaxRoomNumber; i++) // Starts from 1.
 	{
		GetRandomRoom();
		RoomSizes.Add(RoomSize);
		RoomPositions.Add(RoomPosition);
		UE_LOG(LogTemp, Log, TEXT("Room number %d : %s, %s "), i, *RoomSizes[i].ToString(), *RoomPositions[i].ToString());
	
	}
	
}

void ADungeonGen::GenerateRoom()
{
	UStaticMesh* DungeonRoom =LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
	for (int32 i = 0 ; i < MaxRoomNumber; i++)
	{
		 if (DungeonRoom)
		 {
		 	AStaticMeshActor* ActorRoom = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
		 	ActorRoom->SetMobility(EComponentMobility::Movable); 
		 	ActorRoom->GetStaticMeshComponent()->SetStaticMesh(DungeonRoom);
		 	FTransform Transform;
		 	Transform.SetScale3D(FVector(RoomSizes[i].X * 0.1, RoomSizes[i].Y * 0.1 , 1.f));
		 	Transform.SetLocation(FVector(RoomPositions[i].X, RoomPositions[i].Y, 50.f));
		 	ActorRoom->SetActorTransform(Transform);
		 }
	}
}


// Need the duplication check function. 

