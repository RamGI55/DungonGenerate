// Fill out your copyright notice in the Description page of Project Settings.

// DESC:: Please tell me which features will be placed in the main dungeon. 

#include "DungeonMaker/MasterRoom.h"

#include "Kismet/KismetArrayLibrary.h"


// Sets default values
AMasterRoom::AMasterRoom()
{
	// generate the meshes at the very begining, those meshes must be editable in the blueprint.
	// 모든 매쉬는 블루프린트에서 수정 가능함! 
	Floormesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionArrow"));
	NorthExit = CreateDefaultSubobject<UArrowComponent>(TEXT("NorthExit"));
	SouthExit = CreateDefaultSubobject<UArrowComponent>(TEXT("SouthExit"));
	WestExit = CreateDefaultSubobject<UArrowComponent>(TEXT("WestExit"));
	EastExit = CreateDefaultSubobject<UArrowComponent>(TEXT("EastExit"));

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
}





