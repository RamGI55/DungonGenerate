

// This source code is for the portfoilo purpose.

// ---------------------------------------------------- //
// Project Name: Endless Spiral							//
// File Name: DungeonGen.h								//
// Written by: Hyunsoo Park								//
// Edited by:											//
// Generated Date: Mar 07, 2025							//
// Modified Date: Mar 10, 2025							//
// ----------------------------------------------------	//

// DEC : This is the actor class for the random map generation. 


#include "DungeonGen.h"
#include "Engine/StaticMeshActor.h"


void ADungeonGen::BeginPlay()
{
	
	Super::BeginPlay();

	GetGridCoordinates(FVector2D((0, 0, 0)));
	DrawDebugGrid();
	PlacetheRoom();
	GenerateRoom();

	
}

// Sets default values
ADungeonGen::ADungeonGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxRoomNumber = 15;
	iMinRoomSize = 250;
	iMaxRoomSize = 700;
	iMazeSize = 25000;

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
	const int32 x = FMath::RandRange(0, RoomPosXMax);
	const int32 y = FMath::RandRange(0, RoomPosYMax);
	const FVector2D Pos(x, y);
	// Getter 
	RoomPosition = Pos;
} 

void ADungeonGen::PlacetheRoom()
{
	const int32 MaxAttempts = 10; // Maximum attempts per room

	for (int32 i = 0; i < MaxRoomNumber; i++) 
	{
		int32 Attempts = 0;
		bool bPlaced = false;

		while (Attempts < MaxAttempts && !bPlaced)
		{
			GetRandomRoom();
			Attempts++;

			if (!isDuplicated(RoomPosition, RoomSize))
			{
				RoomSizes.Add(RoomSize);
				RoomPositions.Add(RoomPosition);

				FIntPoint GridCoord = GetGridCoordinates(RoomPosition);
				RoomGrid.FindOrAdd(GridCoord).Add(i);
				UE_LOG(LogTemp, Log, TEXT("Room %d placed at %s"), i, *RoomPosition.ToString());

				bPlaced = true; // Room successfully placed
			}
		}

		if (!bPlaced)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to place room %d after %d attempts"), i, MaxAttempts);
		}
	}
}

void ADungeonGen::GenerateRoom()
{
	UStaticMesh* DungeonRoom = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube.Cube"));
	for (int32 i = 0; i < MaxRoomNumber; i++)
	{
		if (DungeonRoom)
		{
			AStaticMeshActor* ActorRoom = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
			ActorRoom->SetMobility(EComponentMobility::Movable);
			ActorRoom->GetStaticMeshComponent()->SetStaticMesh(DungeonRoom);
			FTransform Transform;
			Transform.SetScale3D(FVector(RoomSizes[i].X * 0.1, RoomSizes[i].Y * 0.1, 1.f));
			Transform.SetLocation(FVector(RoomPositions[i].X, RoomPositions[i].Y, 50.f));
			ActorRoom->SetActorTransform(Transform);
		}
	}
}


// Need the duplication check function. 
bool ADungeonGen::isDuplicated(const FVector2D& NewPos, const FVector2D& NewSize)
{
	FBox2D NewRoomBox(NewPos - NewSize * 0.5f, NewPos + NewSize * 0.5f);
	FIntPoint GridPos = GetGridCoordinates(NewPos);
	for (int32 i = -1; i <= 1; i++)
	{
		for (int32 j = -1; j <= 1; j++)
		{
			FIntPoint NeighborPos = GridPos + FIntPoint(i, j);

			if (!RoomGrid.Contains(NeighborPos)) continue; // Skip empty grid cells

			for (int32 RoomIndex : RoomGrid[NeighborPos])
			{
				FBox2D ExistingRoomBox(RoomPositions[RoomIndex] - RoomSizes[RoomIndex] * 0.5f,
									   RoomPositions[RoomIndex] + RoomSizes[RoomIndex] * 0.5f);

				if (NewRoomBox.Intersect(ExistingRoomBox))
				{
					return true; // Found an overlapping room
				}
			}
		}
	}
	return false;
}
	


FIntPoint ADungeonGen::GetGridCoordinates(const FVector2D& position)
{
	return FIntPoint(FMath::FloorToInt(position.X/GridCellSize), FMath::FloorToInt(position.Y/GridCellSize)); 
}

void ADungeonGen::DrawDebugGrid()
{
	const int32 NumCellsX = iMazeSize / GridCellSize; // Total columns
	const int32 NumCellsY = iMazeSize / GridCellSize; // Total rows

	for (int32 x = 0; x <= NumCellsX; x++)
	{
		for (int32 y = 0; y <= NumCellsY; y++)
		{
			FVector Start(x * GridCellSize, y * GridCellSize, 10.0f);
			FVector EndX((x + 1) * GridCellSize, y * GridCellSize, 10.0f);
			FVector EndY(x * GridCellSize, (y + 1) * GridCellSize, 10.0f);

			// Draw horizontal line
			DrawDebugLine(GetWorld(), Start, EndX, FColor::Green, true, 10.0f, 0, 5.0f);

			// Draw vertical line
			DrawDebugLine(GetWorld(), Start, EndY, FColor::Green, true, 10.0f, 0, 5.0f);
		}
	}
}




