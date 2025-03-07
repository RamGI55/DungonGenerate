
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

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonGen.generated.h"

UCLASS()
class DUNGONGENERATE_API ADungeonGen : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	// Sets default values for this actor's properties
	ADungeonGen();
	UFUNCTION(BlueprintCallable, Category = "DungeonGen")
	void GetRandomRoom();
	UFUNCTION(BlueprintCallable, Category = "DungeonGen")
	void PlacetheRoom();
	//UFUNCTION(BlueprintCallable, Category = "DungeonGen")
	//bool isRoomOverlapped();
	UFUNCTION(BlueprintCallable, Category = "DungeonGen")
	void GenerateRoom();

protected:
private:
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 iMazeSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 iMaxRoomSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 iMinRoomSize;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 MaxRoomNumber;
	



protected:
private:
	UPROPERTY(CallInEditor)
	FVector2D RoomPosition;
	UPROPERTY(CallInEditor)
	FVector2D RoomSize; 
	UPROPERTY(EditAnywhere)
	TArray<FVector2D> RoomSizes;
	UPROPERTY(EditAnywhere)
	TArray<FVector2D> RoomPositions;
	
};
