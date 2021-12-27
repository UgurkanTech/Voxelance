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


static bool chunkContains(TArray<AChunkActor*> chunks, FVector v)
{
	for (int i = 0; i < chunks.Num(); i++)
		if(chunks[i]->pos == v) return true;
	return false;
}


uint32 WorldWorker::Run()
{
	// Peform your processor intensive task here. In this example, a neverending
	// task is created, which will only end when Stop is called.
		//srand(actor->id);
	//UE_LOG(LogTemp, Warning, TEXT("id: %d"), rand() % 10);
	//UE_LOG(LogTemp, Warning, TEXT("worldworker running"));

	APawn* pc = nullptr;
	FVector loc(0,0,0);
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
		int size = 1600;
		int range = 3;
		worldgen->chunksInRange.Reset(((range * 2) - 1) * ((range * 2) - 1));
		worldgen->chunksInRange.Add(new FVector(size * ( ffloor(loc.X / size)), (ffloor(loc.Y / size)) * size, 0));
		for (int r = 0; r < range; r++) {
			for (int x = -r; x < r; x++)
				worldgen->chunksInRange.Add(new FVector((x + ffloor(loc.X / size)) * size, (r + ffloor(loc.Y / size)) * size, 0));
			for (int x = r; x > -r; x--)
				worldgen->chunksInRange.Add(new FVector((r + ffloor(loc.X / size)) * size, (x + ffloor(loc.Y / size)) * size, 0));
			for (int x = r; x > -r; x--)
				worldgen->chunksInRange.Add(new FVector((x + ffloor(loc.X / size)) * size, ((r * -1) + ffloor(loc.Y / size)) * size, 0));
			for (int x = -r; x < r; x++)
				worldgen->chunksInRange.Add(new FVector(((r * -1) + ffloor(loc.X / size)) * size, (x + ffloor(loc.Y / size)) * size, 0));

		}

		
		for (int i = 0; i < worldgen->chunksInRange.Num(); i++)
		{
			//UE_LOG(LogTemp, Warning, TEXT("A chunk pos: %.0f %.0f %.0f"), worldgen->chunksInRange[i]->X, worldgen->chunksInRange[i]->Y, worldgen->chunksInRange[i]->Z);
				
			if(!chunkContains(worldgen->chunks, *worldgen->chunksInRange[i]) && !worldgen->generateQueue.Contains(worldgen->chunksInRange[i]))
			{
				
				worldgen->generateQueue.Push(worldgen->chunksInRange[i]);
				//UE_LOG(LogTemp, Warning, TEXT("A chunk pos added: %.0f %.0f %.0f"), worldgen->chunksInRange[i]->X, worldgen->chunksInRange[i]->Y, worldgen->chunksInRange[i]->Z);
				
			}
				
		}
		
		//add ready chunks to render queue
		for (size_t i = 0; i < worldgen->chunks.Num(); i++) {

			if (!worldgen->chunks[i]->dirty && !worldgen->RenderQueue.Contains(worldgen->chunks[i])) {
				worldgen->chunks[i]->chunkWorker->Thread->WaitForCompletion();
				worldgen->RenderQueue.Add(worldgen->chunks[i]);
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