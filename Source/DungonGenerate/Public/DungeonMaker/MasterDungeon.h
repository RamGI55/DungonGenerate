// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MasterRoom.h"
#include "GameFramework/Actor.h"
#include "MasterDungeon.generated.h"

UCLASS()
class DUNGONGENERATE_API AMasterDungeon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterDungeon();
	UFUNCTION(BlueprintCallable)
	AActor* GetMasterDungeon(); 
	UFUNCTION(BlueprintCallable)
	void GetTheInitialDungeon();
	UFUNCTION(BlueprintCallable)
	void GetNextRoom(); 
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	class AMasterRoom* MasterRoom;  
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Spawning")
	//TObjectPtr<UBlueprint> SpnMasterDungeon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RoomList")
	TArray<AActor*> RoomList; 
	
private:
	FTimerHandle TimerHandle; 
	
};
