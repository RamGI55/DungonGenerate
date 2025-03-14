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
	void GetEvent();
	
protected:
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<FString> EventNames;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FString EventName; 
	
	
};
