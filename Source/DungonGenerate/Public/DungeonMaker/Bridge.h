// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bridge.generated.h"

UCLASS()
class DUNGONGENERATE_API ABridge : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABridge();

public:
	UPROPERTY(VisibleAnywhere, Category = "Bridge Components")
	UStaticMeshComponent* BridgeMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Bridge Components")
	float BridgeLength = 10.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Bridge Components")
	float BridgeWidth = 10.f;

	
	
};
