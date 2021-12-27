// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGen.h"

// Sets default values
AWorldGen::AWorldGen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnParams.bAllowDuringConstructionScript = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.bNoFail = true;

	
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

void AWorldGen::SpawnChunk()
{
	World = GetWorld();
	if (World == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Invalid World!")));
		UE_LOG(LogTemp, Error, TEXT("Invalid World!"));
		return;
	}
	UtilityTimer timer;
	int32 t = 0;
	timer.tick();
	for (size_t i = 0; i < 16; i++)
	{
		
		for (size_t j = 0; j < 16; j++)
		{
			
			//spawnLocation = FVector(i * xyMax * triangleSize, j * xyMax * triangleSize, 0);

			//actor = GetWorld()->SpawnActor<AActor>(chunkBP->GeneratedClass, spawnLocation, GetActorRotation(), SpawnParams);
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Invalid %s"), actor->IsActorInitialized()));

			
			//AChunk* c = Cast<AChunk>(actor);
			//c->pos = spawnLocation;
			//c->RerunConstructionScripts();
			//UClass* ClassToCreate = AChunkActor::StaticClass();
			//if (!ClassToCreate->IsValidLowLevelFast()) { return; }
			//TSubclassOf<AChunkActor> ClassToCreate;
			//auto FreshObject = NewObject<AChunkActor>(this, "asd", RF_NoFlags, ClassToCreate.GetDefaultObject());
			//FreshObject->RegisterAllComponents();
			//FreshObject->RegisterComponentWithWorld(World);
			//ch->id = i * j;
			
			
			//UE_LOG(LogTemp, Warning, TEXT("Added thread: %.1f %.1f"), spawnLocation.X, spawnLocation.Y);

			//ch->SetActorLocation(spawnLocation);
			//UE_LOG(LogTemp, Error, TEXT("WorldGen loc %.1f %.1f %.1f"), ch->pos.X, ch->pos.Y, ch->pos.Z);
			//UChunk* chc = Cast<UChunk>(ch);
			//chc->ReceiveBeginPlay();
			
			//chunks.Add(spawnLocation, reinterpret_cast<int64>(c));
			// 
			
			//UE_LOG(LogTemp, Warning, TEXT("debug time: % d"), timer.tock());
		}
		
	}



	t = timer.tock();
	UE_LOG(LogTemp, Warning, TEXT("total debug time: % d"), t);
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Total world gen time: % d"), t));
	
}



// Called when the game starts or when spawned
void AWorldGen::BeginPlay()
{
	Super::BeginPlay();
	SpawnChunk();
	if(ww == nullptr)
		ww = new WorldWorker(this);
}

void AWorldGen::EndPlay(EEndPlayReason::Type type)
{
	Super::EndPlay(type);
	ww->bRunThread = false;
	ww->Thread->Kill();

}

bool AWorldGen::chunkContains(FVector* v)
{
	for (int i = 0; i < chunks.Num(); i++)
		if(chunks[i]->Pos.Equals(*v)) return true;
	return false;
}


// Called every frame
void AWorldGen::Tick(float DeltaTime)
{
	if (mutex.tryLock())
	{
		for (FVector* v : chunksInRange)
		{
			if (!chunkContains(v))
			{
				chunks.Add(new FChunkBlock(v));
			}
		}
		bool done = false;
		for (FChunkBlock* c : chunks)
		{
		
			switch (c->State)
			{
			case Pooled:
				{
					AChunkActor* ch;
					if(chunkActorPool.IsEmpty())
						 ch = World->SpawnActor<AChunkActor>(AChunkActor::StaticClass(), c->Pos, FRotator(0,0,0), SpawnParams);
					else
					{
						chunkActorPool.Dequeue(ch);
						ch->dirty = true;
					}
						
					ch->pos = c->Pos;
					ch->SetActorLocation(c->Pos);
					c->Actor = ch;
					ch->Start(&cmg, &cbg);
					c->State = Dirty;
					UE_LOG(LogTemp, Warning, TEXT("A chunk Dirty: %.0f %.0f %.0f"), c->Pos.X, c->Pos.Y, c->Pos.Z);
					done = true;
				}
				break;
			case Dirty:
				{
					if(!c->Actor->dirty)
						c->State = ReadyToRender;
				}
				break;
			case ReadyToRender:
				{
					c->Actor->mesh->CreateMeshSection(0, c->Actor->vertices, c->Actor->triangles, TArray<FVector>(), c->Actor->UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
					c->State = Rendered;
					UE_LOG(LogTemp, Warning, TEXT("A chunk Rendered: %.0f %.0f %.0f"), c->Pos.X, c->Pos.Y, c->Pos.Z);
					done = true;
				}
				break;
			case Rendered:
				{
				
				}
				break;
			case ToBeDeleted:
				{
					c->Actor->mesh->ClearAllMeshSections();
					c->State = Deleted;
					chunkActorPool.Enqueue(c->Actor);
					chunks.Remove(c);
					UE_LOG(LogTemp, Warning, TEXT("A chunk Deleted: %.0f %.0f %.0f"), c->Pos.X, c->Pos.Y, c->Pos.Z);
					done = true;
				}
				break;
			}
		
			

			if(done)
				break;
		}
		mutex.Unlock();
	}

}

