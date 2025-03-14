// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonMaker/Bridge.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABridge::ABridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BridgeMesh = CreateDefaultSubobject<UStaticMeshComponent>("BridgeMesh");
	RootComponent = BridgeMesh;
	// Set the mesh as dynamic
	BridgeMesh->SetMobility(EComponentMobility::Movable);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BridgeMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (BridgeMeshAsset.Succeeded())
	{
		BridgeMesh->SetStaticMesh(BridgeMeshAsset.Object);
	}
	BridgeMesh->SetRelativeScale3D(FVector(BridgeLength, BridgeWidth, 0.5f));

}



