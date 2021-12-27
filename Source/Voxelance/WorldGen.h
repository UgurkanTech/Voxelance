// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <wrl/wrappers/corewrappers.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkActor.h"
#include "ChunkMeshGenerator.h"
#include "ChunkBlockGen.h"
#include "Mutex.h"
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
	UPROPERTY()
	TArray<AChunkActor*> chunks;
	UPROPERTY()
	TArray<AChunkActor*> RenderQueue;
	TArray<FVector*> generateQueue;
	TArray<FVector*> chunksInRange;
	

	Mutex mutex;
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
	
	AActor* actor;
	ChunkMeshGenerator cmg;
	ChunkBlockGen cbg;
};
