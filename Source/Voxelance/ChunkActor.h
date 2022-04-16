// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Misc/Crc.h"
#include "ChunkMeshGenerator.h"
#include "ChunkBlockGen.h"
#include <Thread>

//#include "ChunkBlock.h"
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
//struct FChunkBlock;

UCLASS(BlueprintType, Blueprintable)
class VOXELANCE_API AChunkActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChunkActor();
	void Start(ChunkMeshGenerator* cmg, ChunkBlockGen* cbg);
	FVector pos;
	int id;
	bool dirty;
	UPROPERTY()
	TArray<FVector> vertices;
	UPROPERTY()
	TArray<int32> triangles;
	UPROPERTY()
	TArray<FVector2D> UVs;
	UPROPERTY()
	UProceduralMeshComponent* mesh;
	UPROPERTY()
	UMaterial* StoredMaterial;
	
	ChunkWorker* chunkWorker;
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterialInst;
	UPROPERTY()
	FBlock blocks[blockCount];
	
	//FChunkBlock* chunkBlock;
	//TSharedPtr<FChunkBlock> chunkBlock;
	bool operator==(const AChunkActor& a) const
	{
		return pos.X == a.pos.X && pos.Y == a.pos.Y && pos.Z == a.pos.Z;
	}

	UFUNCTION(BlueprintCallable)
	FBlock getBlock(int x, int y, int z);
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void setBlock(int x, int y, int z, FBlock block);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type type) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
