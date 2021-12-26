// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkActor.h"
#include "ChunkMeshGenerator.h"
#include "ChunkBlockGen.h"
#include "Containers/Queue.h"
#include "WorldWorker.h"
#include "WorldGen.generated.h"

class WorldWorker;
UCLASS()
class VOXELANCE_API AWorldGen : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldGen();

	UFUNCTION()
		void SpawnChunk();

	//TArray<*AChunk> chunks;
	TMap<FVector, AChunkActor*> chunks;
	TArray<AChunkActor*> DirtyChunks;
	TQueue<AChunkActor*, EQueueMode::Mpsc> generatedChunkToRender;
	TArray<FVector*> chunksInRange;

	WorldWorker* ww;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type type) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UBlueprint* chunkBP;
	UWorld* World;
	FActorSpawnParameters SpawnParams;
	FVector spawnLocation;
	AActor* actor;
	ChunkMeshGenerator cmg;
	ChunkBlockGen cbg;
};
