// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DungeonEventComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGONGENERATE_API UDungeonEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDungeonEventComponent();
	UFUNCTION(BlueprintCallable)
	void AddEvent(TArray<FString> EventName);

protected:
	
public:	
	TArray<FString> EventNames;
	
	
};
