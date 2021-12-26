// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Misc/Crc.h"
#include "ChunkMeshGenerator.h"
#include "ChunkBlockGen.h"
#include <Thread>
#include "ChunkWorker.h"
#include "ChunkActor.generated.h"

using namespace std;

#define xyMax 16
#define xyMax2 256
#define xyMaxSub1 15
#define zMax 255
#define blockCount 65280
#define tileSize 4.0f
#define triangleSize 50


class ChunkMeshGenerator;
class ChunkBlockGen;
class ChunkWorker;
UCLASS()
class VOXELANCE_API AChunkActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkActor();
	void Start(ChunkMeshGenerator* cmg, ChunkBlockGen* cbg);
	FVector pos;
	int id;

	TArray<FVector> vertices;
	TArray<int32> triangles;
	TArray<FVector2D> UVs;
	UProceduralMeshComponent* mesh;
	UMaterial* StoredMaterial;
	ChunkWorker* chunkWorker;
	UMaterialInstanceDynamic* DynamicMaterialInst;
	FBlock blocks[blockCount];

	bool operator==(const AChunkActor& a) const
	{
		return pos.X == a.pos.X && pos.Y == a.pos.Y && pos.Z == a.pos.Z;
	}
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type type) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
