// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <wrl/wrappers/corewrappers.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChunkActor.h"
#include "ChunkBlock.h"
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
	
	TArray<FChunkBlock*> chunks;
	TQueue<FChunkBlock*> chunkPool;
	TArray<FVector*> chunksInRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;
	bool chunkContains(FVector* v);
	Mutex mutex;
	WorldWorker* ww;
	static ChunkMeshGenerator* cmg;
	static ChunkBlockGen* cbg;
	
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
	AChunkActor* ch;
	bool done;
	FChunkBlock* cbtemp;
	AActor* actor;
	
};
