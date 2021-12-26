// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldWorker.h"

#pragma region Main Thread Code
WorldWorker::WorldWorker(AWorldGen* wg)
{
	this->worldgen = wg;
	Thread = FRunnableThread::Create(this, TEXT("WorldWorker"));
}

WorldWorker::~WorldWorker()
{
	if (Thread)
	{
		bRunThread = false;
		// Kill() is a blocking call, it waits for the thread to finish.
		// Hopefully that doesn't take too long
		Thread->Kill();
		delete Thread;
	}

}
#pragma endregion


bool WorldWorker::Init()
{
	//UE_LOG(LogTemp, Warning, TEXT("My custom thread has been initialized"))
	bRunThread = true;
		// Return false if you want to abort the thread
	return true;
}

int inline ffloor(const float x) { return x < 0 ? (int)x == x ? (int)x : (int)x - 1 : (int)x; }


uint32 WorldWorker::Run()
{
	// Peform your processor intensive task here. In this example, a neverending
	// task is created, which will only end when Stop is called.
		//srand(actor->id);
	//UE_LOG(LogTemp, Warning, TEXT("id: %d"), rand() % 10);
	//UE_LOG(LogTemp, Warning, TEXT("worldworker running"));

	APawn* pc = nullptr;
	FVector loc;
	while (bRunThread){
		if (pc == nullptr) {
			pc = worldgen->GetWorld()->GetFirstPlayerController()->GetPawn();
		}
		else
		{
			loc = pc->GetActorLocation();
		}
	

		//UE_LOG(LogTemp, Warning, TEXT("Playerpos: %.1f %.1f %.1f"), loc.X, loc.Y, loc.Z);

		//Find chunks
		int size = 800;
		int range = 4;
		worldgen->chunksInRange.Reset(((range * 2) - 1) * ((range * 2) - 1));
		worldgen->chunksInRange.Add(new FVector((size * (0 + ffloor(loc[0] / size)), (0 + ffloor((loc[1] / size))) * size)));
		for (int r = 0; r < range; r++) {
			for (int x = -r; x < r; x++)
				worldgen->chunksInRange.Add(new FVector(((x + ffloor((loc[0] / size))) * size, (r + ffloor((loc[1] / size))) * size)));
			for (int x = r; x > r; x--)
				worldgen->chunksInRange.Add(new FVector(((r + ffloor((loc[0] / size))) * size, (x + ffloor((loc[1] / size))) * size)));
			for (int x = r; x > r; x--)
				worldgen->chunksInRange.Add(new FVector(((x + ffloor((loc[0] / size))) * size, (r * -1 + ffloor((loc[1] / size))) * size)));
			for (int x = -r; x < r; x++)
				worldgen->chunksInRange.Add(new FVector(((r * -1 + ffloor((loc[0] / size))) * size, (x + ffloor((loc[1] / size))) * size)));
		}

		//add ready chunks to render queue
		for (size_t i = 0; i < worldgen->DirtyChunks.Num(); i++) {

			if (worldgen->DirtyChunks[i]->chunkWorker->created) {
				worldgen->DirtyChunks[i]->chunkWorker->Thread->WaitForCompletion();
				worldgen->generatedChunkToRender.Enqueue(worldgen->DirtyChunks[i]);
				worldgen->DirtyChunks.RemoveAt(i);
				//UE_LOG(LogTemp, Warning, TEXT("chunk removed: %d, new size %d"), i, worldgen->generatingChunks.Num());
				//i--;
				//break;
			}

		}
		FPlatformProcess::Sleep(0.05f);
	}

	return 0;
}


// This function is NOT run on the new thread!
void WorldWorker::Stop()
{
	// Clean up memory usage here, and make sure the Run() function stops soon
	// The main thread will be stopped until this finishes!

	// For this example, we just need to terminate the while loop
	// It will finish in <= 1 sec, due to the Sleep()
	bRunThread = false;
}