// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkWorker.h"

#pragma region Main Thread Code
ChunkWorker::ChunkWorker(AChunkActor* actor, ChunkBlockGen* cbg, ChunkMeshGenerator* cmg)
{
	this->cbg = cbg;
	this->cmg = cmg;
	this->actor = actor;
	Thread = FRunnableThread::Create(this, TEXT("ChunkWorker"));
	
	
}

ChunkWorker::~ChunkWorker()
{
	if (Thread)
	{
		// Kill() is a blocking call, it waits for the thread to finish.
		// Hopefully that doesn't take too long
		Thread->Kill();
		delete Thread;
	}
}
#pragma endregion
// The code below will run on the new thread.

bool ChunkWorker::Init()
{

	//UE_LOG(LogTemp, Warning, TEXT("My custom thread has been initialized"))

		// Return false if you want to abort the thread
	return true;
}
class UtilityTimer
{
	int64 TickTime = 0;
	int64 TockTime = 0;
public:
	int64 unixTimeNow()
	{
		FDateTime timeUtc = FDateTime::UtcNow();
		return timeUtc.ToUnixTimestamp() * 1000 + timeUtc.GetMillisecond();
	}

	void tick()
	{
		TickTime = unixTimeNow();
	}

	int32 tock()
	{
		TockTime = unixTimeNow();
		return TockTime - TickTime;
	}
};


uint32 ChunkWorker::Run()
{
	// Peform your processor intensive task here. In this example, a neverending
	// task is created, which will only end when Stop is called.
	//while (bRunThread){
	srand(actor->id);
	//UE_LOG(LogTemp, Warning, TEXT("id: %d"), rand() % 10);
	UtilityTimer timer;
	int32 t = 0;
	timer.tick();
	cbg->generateBlocks(actor->pos.X / triangleSize / 2, actor->pos.Y / triangleSize / 2, actor->pos.Z / triangleSize / 2, actor->blocks);
	cmg->generateMesh(actor->blocks, actor->vertices, actor->triangles, actor->UVs);
	//FPlatformProcess::Sleep(rand() % 1000 / 100.0);
	t = timer.tock();
	//UE_LOG(LogTemp, Warning, TEXT("A chunk generated in: %d at pos: %.0f %.0f %.0f"), t, actor->pos.X, actor->pos.Y, actor->pos.Z);
	actor->dirty = false;
	//}

	return 0;
}


// This function is NOT run on the new thread!
void ChunkWorker::Stop()
{
	// Clean up memory usage here, and make sure the Run() function stops soon
	// The main thread will be stopped until this finishes!

	// For this example, we just need to terminate the while loop
	// It will finish in <= 1 sec, due to the Sleep()
	bRunThread = false;
}