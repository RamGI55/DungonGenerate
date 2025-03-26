// Fill out your copyright notice in the Description page of Project Settings.

// Version 2 Edition - 03. 21. 2025 2:00PM

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MasterRoom.generated.h"


class USphereComponent;
class AMasterDungeon;

UCLASS()
class DUNGONGENERATE_API AMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterRoom();
	
	UFUNCTION (BlueprintCallable)
	FVector GetRandDirection();
	UFUNCTION (BlueprintCallable)
	TArray<FVector> GetRouteDirection();


	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	bool IsDirectionDuplicated(const FVector& Direction);
	UFUNCTION(BlueprintCallable)
	const bool SphereTracing();
	UFUNCTION(BlueprintCallable)
	void ActivateEvent();


protected:
	UFUNCTION()
	bool CollisionDetected(USphereComponent* CollisionComponent); // must return the value. 
	UFUNCTION(BlueprintCallable)
	void ClearBridge(); 
	
public:	
	// Static Mashes
	UPROPERTY(VisibleAnywhere,Category="SpawnBP")
	TSubclassOf<class UObject> SpwnDungeon;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Floormesh;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;
	// Master Direction Arrow indicates the North. 
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* NorthArrow;
	// Direction Arrows 
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* NorthExit;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* SouthExit;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* WestExit;
	UPROPERTY(VisibleAnywhere )
	UArrowComponent* EastExit;
	 
	// Walls
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* NorthWall;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SouthWall;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WestWall;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EastWall;

	// Actor Spawn position
	UPROPERTY (EditAnywhere)
	UScene* NonPlayerSpawnPos;
	
	// Collision Sphere for overlap check
	UPROPERTY(VisibleAnywhere, Category = "Trace")
	float Traceradius = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Trace")
	int32 HitCount;
	UPROPERTY(VisibleAnywhere, Category = "Event")
	class UDungeonEventComponent* EventComponent;
	
	// Direction Arrow Array for the random generating direction. 
	UPROPERTY(EditAnywhere, Category = "Arrows")
	TArray<UArrowComponent*> DirectionArrows;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* RandDirection;
	UPROPERTY()
	AMasterDungeon* DungeonGenerator;

	// Bridge Array
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* NorthBridge;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SouthBridge;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* WestBridge;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EastBridge;
	
	
	// Direction Collision Array
	UPROPERTY(VisibleAnywhere)
	USphereComponent* NorthCollision;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SouthCollision;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* WestCollision;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* EastCollision; 
	UPROPERTY(VisibleAnywhere)
	TArray<USphereComponent*> DirectionCollisions; 

	// Collision for the Event (Open the Gate)
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* NorthEventCollision;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* SouthEventCollision;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WestEventCollision;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* EastEventCollision;
	TArray<UBoxComponent*> EventCollisions;
	
	
};
