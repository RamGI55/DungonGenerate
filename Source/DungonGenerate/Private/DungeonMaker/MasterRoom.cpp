// Fill out your copyright notice in the Description page of Project Settings.

// Version 2 Edition - 03. 21. 2025 2:00PM 

#include "DungeonMaker/MasterRoom.h"

#include "Components/SphereComponent.h"
#include "DungeonMaker/DungeonEventComponent.h"
#include "DungeonMaker/MasterDungeon.h"


// Sets default values
AMasterRoom::AMasterRoom()
{	
	Floormesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floormesh"));
	//Floormesh->SetRelativeLocation(FVector(0, 0, 0.f));
	//Floormesh->SetRelativeScale3D(FVector(25.f, 25.f, 0.5f));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetRelativeLocation(FVector(0, 0, 0.f));
	CollisionBox->SetRelativeScale3D(FVector(25.f, 25.f, 1.f));

	NorthArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("NorthArrow"));
	NorthArrow->SetRelativeLocation(FVector(35.f, 35.f, 120.f));
	NorthArrow->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	NorthExit = CreateDefaultSubobject<UArrowComponent>(TEXT("NorthExit"));
	NorthExit->SetRelativeLocation(FVector(0.f, -3450.f, 0.f));
	NorthExit->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	NorthExit->ArrowColor = FColor::Green;

	SouthExit = CreateDefaultSubobject<UArrowComponent>(TEXT("SouthExit"));
	SouthExit->SetRelativeLocation(FVector(0.f, 3450.f, 0.f));
	SouthExit->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
	SouthExit->ArrowColor = FColor::Green;

	WestExit = CreateDefaultSubobject<UArrowComponent>(TEXT("WestExit"));
	WestExit->SetRelativeLocation(FVector(-3450.f, 0.f, 0.f));
	WestExit->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	WestExit->ArrowColor = FColor::Green;

	EastExit = CreateDefaultSubobject<UArrowComponent>(TEXT("EastExit"));
	EastExit->SetRelativeLocation(FVector(3450.f, 0.f, 0.f));
	EastExit->ArrowColor = FColor::Green;

	EventComponent = CreateDefaultSubobject<UDungeonEventComponent>(TEXT("EventComponent"));
	
	DirectionArrows.Add(NorthExit);
	DirectionArrows.Add(SouthExit);
	DirectionArrows.Add(WestExit);
	DirectionArrows.Add(EastExit);

	// Bridge
	NorthBridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NorthBridge"));
	NorthBridge->SetupAttachment(Floormesh);
	
	SouthBridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SouthBridge"));
	SouthBridge->SetupAttachment(Floormesh);
	WestBridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WestBridge"));
	WestBridge->SetupAttachment(Floormesh);
	EastBridge = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EastBridge"));
	EastBridge->SetupAttachment(Floormesh);
	

	// Collision to check the bridge direction
	NorthCollision = CreateDefaultSubobject<USphereComponent>(TEXT("NorthCollision"));
	NorthCollision->SetupAttachment(NorthBridge);
	SouthCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SouthCollision"));
	SouthCollision->SetupAttachment(SouthBridge);
	WestCollision = CreateDefaultSubobject<USphereComponent>(TEXT("WestCollision"));
	WestCollision->SetupAttachment(WestBridge);
	EastCollision = CreateDefaultSubobject<USphereComponent>(TEXT("EastCollision"));
	EastCollision->SetupAttachment(EastBridge);

	DirectionCollisions.Add(NorthCollision);
	DirectionCollisions.Add(SouthCollision);
	DirectionCollisions.Add(WestCollision);
	DirectionCollisions.Add(EastCollision);
	
	SphereTracing();
	
}

FVector AMasterRoom::GetRandDirection()
{
    // Check for duplicated directions and remove them from the array
    TArray<UArrowComponent*> ValidDirections;
    for (UArrowComponent* Arrow : DirectionArrows)
    {
        if (!IsDirectionDuplicated(Arrow->GetComponentLocation()))
        {
            ValidDirections.Add(Arrow);
        }
    }

    if (ValidDirections.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("All directions are duplicated. Cannot place new dungeon."))
    	return FVector::ZeroVector; // Return an invalid vector
    }

    int32 i = FMath::RandRange(0, ValidDirections.Num() - 1);

    //UE_LOG(LogTemp, Display, TEXT("RandDirection %d"), i);
    RandDirection = ValidDirections[i];
    return RandDirection->GetComponentLocation();
}

TArray<FVector> AMasterRoom::GetRouteDirection()
{
	TArray<FVector> Directions;
	for (UArrowComponent* Arrow : DirectionArrows)
	{
		if (IsDirectionDuplicated(Arrow->GetComponentLocation()))
		{
			Directions.Add(Arrow->GetComponentLocation());
		}
		else
		{
			break;
		}
	}
	return Directions;
}

void AMasterRoom::BeginPlay()
{
    Super::BeginPlay();
	// ClearBridge(); 
   
}

bool AMasterRoom::IsDirectionDuplicated(const FVector& Direction) // TArray<FVector> 
{
    const FVector Start = GetActorLocation()+Direction;
    const FVector End = Start + Direction;
    TArray<AActor*> ActorsIgnore;
    ActorsIgnore.Add(this);
    TArray<FHitResult> HitResult;
	

    const bool Hit = UKismetSystemLibrary::SphereTraceMulti(
        GetWorld(),
        Start,
        End,
        50.0f, // Trace radius
        UEngineTypes::ConvertToTraceType(ECC_EngineTraceChannel1),
        false,
        ActorsIgnore,
        EDrawDebugTrace::Persistent,
        HitResult,
        true,
        FLinearColor::Yellow,
        FLinearColor::Red,
        5.0f// Duration of the debug line
    );

    if (Hit)
    {
    	for (const FHitResult& Result : HitResult)
    	{
    		AActor* HitActor = Result.GetActor(); 
	        if (HitActor && HitActor->IsA(AMasterRoom::StaticClass()))
	        {
	            return true; // Direction is duplicated
	        }
    	}
    }
    return false; // Direction is not duplicated
}

const bool AMasterRoom::SphereTracing()
{
    TArray<AActor*> ActorsIgnore;
    ActorsIgnore.Add(this);
    FHitResult HitResult;

    for (UArrowComponent* Arrow : DirectionArrows)
    {
        const FVector Start = Arrow->GetComponentLocation();
        const FVector End = Arrow->GetComponentLocation();
        const bool Hit = UKismetSystemLibrary::SphereTraceSingle(
            GetWorld(),
            Start,
            End,
            250.f, // Trace radius
            ETraceTypeQuery::TraceTypeQuery1,
            false,
            ActorsIgnore,
            EDrawDebugTrace::Persistent,
            HitResult,
            true,
            FLinearColor::Blue,
            FLinearColor::Red,
            5.0f // Duration of the debug line
        );

        if (Hit)
        {
            return true;
        }
    }
    return false;
}

void AMasterRoom::ActivateEvent()
{
	EventComponent->GetEvent(); 
}

bool AMasterRoom::CollisionDetected(USphereComponent* CollisionComponent)
{
	for (USphereComponent* Sphere : DirectionCollisions)
	{
		TArray<AActor*> ActorsIgnore;
		ActorsIgnore.Add(this);
		FHitResult HitResult;
		const bool Hit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			Sphere->GetComponentLocation(),
			Sphere->GetComponentLocation(),
			250.f, // Trace radius
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			ActorsIgnore,
			EDrawDebugTrace::Persistent,
			HitResult,
			true,
			FLinearColor::Blue,
			FLinearColor::Red,
			5.0f // Duration of the debug line
		);

		if (Hit && HitResult.GetActor() && HitResult.GetActor()->IsA(AMasterRoom::StaticClass()))
		{
			return true;
		}
	}
	return false;
	
}

void AMasterRoom::ClearBridge()
{
	if (!CollisionDetected(NorthCollision))
	{
		NorthBridge->DestroyComponent();
	}
	if (!CollisionDetected(SouthCollision))
	{
		SouthBridge->DestroyComponent();
	}
	if (!CollisionDetected(WestCollision))
	{
		WestBridge->DestroyComponent();
	}
	if (!CollisionDetected(EastCollision))
	{
		EastBridge->DestroyComponent();
	}
	
}






