// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/MasterRoom.h"


// Sets default values
AMasterRoom::AMasterRoom()
{
	Floormesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floormesh"));
	Floormesh->SetRelativeLocation(FVector(0, 0, 0.f));
	Floormesh->SetRelativeScale3D(FVector(25.f, 25.f, 0.1f));

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
	
	DirectionArrows.Add(NorthExit);
	DirectionArrows.Add(SouthExit);
	DirectionArrows.Add(WestExit);
	DirectionArrows.Add(EastExit);
	
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
        UE_LOG(LogTemp, Error, TEXT("All directions are duplicated. Cannot place new dungeon."));
        return FVector::ZeroVector; // Return an invalid vector
    }

    int32 i = FMath::RandRange(0, ValidDirections.Num() - 1);

    UE_LOG(LogTemp, Display, TEXT("RandDirection %d"), i);
    RandDirection = ValidDirections[i];
    return RandDirection->GetComponentLocation();
}

void AMasterRoom::BeginPlay()
{
    Super::BeginPlay();
    SphereTracing(); 
}

bool AMasterRoom::IsDirectionDuplicated(const FVector& Direction)
{
    const FVector Start = this->GetActorLocation();
    const FVector End = Start + Direction;
    TArray<AActor*> ActorsIgnore;
    ActorsIgnore.Add(this);
    FHitResult HitResult;

    const bool Hit = UKismetSystemLibrary::SphereTraceSingle(
        GetWorld(),
        Start,
        End,
        50.0f, // Trace radius
        ETraceTypeQuery::TraceTypeQuery1,
        false,
        ActorsIgnore,
        EDrawDebugTrace::ForDuration,
        HitResult,
        true,
        FLinearColor::Blue,
        FLinearColor::Red,
        5.0f // Duration of the debug line
    );

    if (Hit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor && HitActor->IsA(AMasterRoom::StaticClass()))
        {
            return true; // Direction is duplicated
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
        const FVector Start = this->GetActorLocation();
        const FVector End = Arrow->GetComponentLocation();
        const bool Hit = UKismetSystemLibrary::SphereTraceSingle(
            GetWorld(),
            Start,
            End,
            50.0f, // Trace radius
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



