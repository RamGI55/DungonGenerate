// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonEventComponent.h"
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
	void SpawnDungeon();
	
private:
	UFUNCTION()
	void DeleteDungeon(); 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AMasterRoom* MasterRoom; 

public:
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TObjectPtr<UBlueprint> SpnMasterDungeon;
	UPROPERTY(VisibleAnywhere, Category = "Dungeon")
	AActor* FirstDungeon;
	UPROPERTY(VisibleAnywhere, Category = "Dungeon")
	AActor* PreviousDungeon;
	UPROPERTY(VisibleAnywhere, Category = "Dungeon")
	TSubclassOf<class UObject> SpwnDungeon;
	UPROPERTY(EditAnywhere, Category = "Dungeon")
	int32 DungeonNumber;
	UPROPERTY(VisibleAnywhere, Category = "Dungeon")
	int32 GenerateCounter; 
	
};
