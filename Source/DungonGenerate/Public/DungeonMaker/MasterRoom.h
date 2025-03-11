// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "MasterRoom.generated.h"

UCLASS()
class DUNGONGENERATE_API AMasterRoom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterRoom();
	UFUNCTION(BlueprintCallable)
	const UArrowComponent* GetRandDirection();
	UFUNCTION(BlueprintCallable)
	void GenerateRoom();
	virtual void BeginPlay() override; 
	

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
	UArrowComponent* Arrow;
	// Direction Arrows 
	UPROPERTY(EditAnywhere)
	UArrowComponent* NorthExit;
	UPROPERTY(EditAnywhere)
	UArrowComponent* SouthExit;
	UPROPERTY(EditAnywhere)
	UArrowComponent* WestExit;
	UPROPERTY(EditAnywhere)
	UArrowComponent* EastExit;
	// Direction Arrow Array for the random generating direction. 
	UPROPERTY(VisibleAnywhere)
	TArray<UArrowComponent*> DirectionArrows;
	UPROPERTY(VisibleAnywhere)
	UArrowComponent* RandDirection; 
	
	
};
