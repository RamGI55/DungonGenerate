// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterRoom.h"


// Sets default values
AMasterRoom::AMasterRoom()
{
	Floormesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floormesh"));
	Floormesh->SetRelativeLocation(FVector(0, 0, 40.f));
	Floormesh->SetRelativeScale3D(FVector(19.2f, 19.2f, 0.5f));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeLocation(FVector(0, 0, 40.f));
	CollisionBox->SetRelativeScale3D(FVector(30.f, 30.f, 1.f));

	NorthArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("NorthArrow"));
	NorthArrow->SetRelativeLocation(FVector(35.f, 35.f, 120.f));
	NorthArrow->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	NorthExit = CreateDefaultSubobject<UArrowComponent>(TEXT("NorthExit"));
	NorthExit->SetRelativeLocation(FVector(14.6f, -950.f, 40.f));
	NorthExit->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	NorthExit->ArrowColor = FColor::Green;

	SouthExit = CreateDefaultSubobject<UArrowComponent>(TEXT("SouthExit"));
	SouthExit->SetRelativeLocation(FVector(14.6f, 950.f, 40.f));
	SouthExit->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	SouthExit->ArrowColor = FColor::Green;

	WestExit = CreateDefaultSubobject<UArrowComponent>(TEXT("WestExit"));
	WestExit->SetRelativeLocation(FVector(-950.5f, 0.f, 40.f));
	WestExit->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	WestExit->ArrowColor = FColor::Green;

	EastExit = CreateDefaultSubobject<UArrowComponent>(TEXT("EastExit"));
	EastExit->SetRelativeLocation(FVector(969.5f, 0.f, 40.f));
	EastExit->ArrowColor = FColor::Green;
	
	DirectionArrows.Add(NorthExit);
	DirectionArrows.Add(SouthExit);
	DirectionArrows.Add(WestExit);
	DirectionArrows.Add(EastExit);
	
}

 FVector AMasterRoom::GetRandDirection()
{
	int32 i = FMath::RandRange( 0 , DirectionArrows.Num() -1 ); 

	UE_LOG(LogTemp, Display, TEXT("RandDirection %d"), i);
	RandDirection = DirectionArrows[i];
	return RandDirection->GetComponentLocation(); 
	
}

void AMasterRoom::BeginPlay()
{
	Super::BeginPlay();
	
}



