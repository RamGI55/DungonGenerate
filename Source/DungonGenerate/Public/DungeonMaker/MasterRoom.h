// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MasterRoom.generated.h"




UCLASS()
class DUNGONGENERATE_API AMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterRoom();
	
	UFUNCTION (BlueprintCallable)
	FVector GetRandDirection(); 
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	bool IsDirectionDuplicated(const FVector& Direction);
	UFUNCTION(BlueprintCallable)
	const bool SphereTracing(); 
protected:


public:	
	// Static Mashes
	UPROPERTY(VisibleAnywhere,Category="SpawnBP")
	TSubclassOf<class UObject> SpwnDungeon;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Floormesh;
	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;
	// Master Direction Arrow indicates the North. 
	UPROPERTY(EditAnywhere)
	UArrowComponent* NorthArrow;
	// Direction Arrows 
	UPROPERTY(EditAnywhere)
	UArrowComponent* NorthExit;
	UPROPERTY(EditAnywhere)
	UArrowComponent* SouthExit;
	UPROPERTY(EditAnywhere)
	UArrowComponent* WestExit;
	UPROPERTY(EditAnywhere)
	UArrowComponent* EastExit;
	
	// Walls
	
	// Collision Sphere for overlap check
	UPROPERTY(VisibleAnywhere, Category = "Trace")
	float Traceradius = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Trace")
	int32 HitCount; 
	
	// Direction Arrow Array for the random generating direction. 
	UPROPERTY(VisibleAnywhere)
	TArray<UArrowComponent*> DirectionArrows;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* RandDirection; 
	
};
