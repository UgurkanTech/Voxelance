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

// Called every frame
void AWorldGen::Tick(float DeltaTime)
{
	AChunkActor* tempActor;
	FVector* tempVector;
	if (RenderQueue.Num() > 0 && mutex.tryLock()) {
		
		tempActor = RenderQueue[0];
		tempActor->mesh->CreateMeshSection(0, tempActor->vertices, tempActor->triangles, TArray<FVector>(), tempActor->UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
		RenderQueue.RemoveAt(0);
		UE_LOG(LogTemp, Warning, TEXT("A chunk rendered at pos: %.0f %.0f %.0f "), tempActor->pos.X, tempActor->pos.Y, tempActor->pos.Z);
		//chunks.Add(tempActor);
		mutex.Unlock();
	}


	
	if(generateQueue.Num() > 0 && mutex.tryLock())
	{
		tempVector = generateQueue[0];
		AChunkActor* ch = World->SpawnActor<AChunkActor>(AChunkActor::StaticClass(), *tempVector, FRotator(0,0,0), SpawnParams);
		ch->pos = *tempVector;
		ch->Start(&cmg, &cbg);
		ch->dirty = false;
		ch->rendered = true;
		chunks.Add(ch);
		generateQueue.RemoveAt(0);
		mutex.Unlock();
	}

}

