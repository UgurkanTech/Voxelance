// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "ChunkBlockGen.h"
#include "HAL/Runnable.h"

/**
 * 
 */
class AChunkActor;
class ChunkBlockGen;
class ChunkMeshGenerator;
class VOXELANCE_API ChunkWorker : public FRunnable
{
public:
	ChunkWorker(AChunkActor* actor, ChunkBlockGen* cbg, ChunkMeshGenerator* cmg);
	virtual ~ChunkWorker() override;
	// Do not call these functions youself, that will happen automatically
	bool Init() override; // Do your setup here, allocate memory, ect.
	uint32 Run() override; // Main data processing happens here
	void Stop() override; // Clean up any memory you allocated here
	bool created;
	AChunkActor* actor;
	ChunkBlockGen* cbg;
	ChunkMeshGenerator* cmg;

	FRunnableThread* Thread;
private:

	// Thread handle. Control the thread using this, with operators like Kill and Suspend
	

	// Used to know when the thread should exit, changed in Stop(), read in Run()
	bool bRunThread;
};
