// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkActor.h"



// Sets default values
AChunkActor::AChunkActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//AmmoSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("AmmoSceneComponent"));
	//RootComponent = AmmoSceneComponent;
	//chunk = CreateDefaultSubobject<USceneComponent, UChunk>("Chunk Mesh", true);
	dirty = true;
	
	//chunk.Rename(NULL, this);
	
	//chunk->SetupAttachment(RootComponent);
	//AddOwnedComponent(chunk);

	//chunk->Rename(TEXT("Asdst"), this);
	//AddComponentByClass(UChunk::GetClass, false, FTransform(), true);
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	
	//Doesnt work
	
	//nc->AttachTo(GetRootComponent());
	//nc->RegisterComponent();
	//AddComponentByClass(nc->GetClass(), false, FTransform(), true);
	


	//chunk = NewObject<UChunk>(UChunk::StaticClass());
	//RootComponent = Cast<USceneComponent>(chunk);
	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
	ReceiveBeginPlay();

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/FirstPersonBP/Blueprints/textures_Mat"));
	if (FoundMaterial.Succeeded())
	{
		StoredMaterial = FoundMaterial.Object;
	}
	DynamicMaterialInst = UMaterialInstanceDynamic::Create(StoredMaterial, mesh);

	mesh->SetMaterial(0, StoredMaterial);

	RootComponent = Cast<USceneComponent>(mesh);
	
}


// Called when the game starts or when spawned
void AChunkActor::BeginPlay()
{
	Super::BeginPlay();
	//chunk->pos = pos;
	
}
void AChunkActor::EndPlay(EEndPlayReason::Type type)
{
	Super::EndPlay(type);
	if(chunkWorker != nullptr && dirty)
		chunkWorker->Thread->Kill();
	

}


void AChunkActor::Start(ChunkMeshGenerator* cmg, ChunkBlockGen* cbg) {

	//UActorComponent* ac = AddComponentByClass(UChunk::StaticClass(), false, FTransform(), false);
	//UChunk* uc = Cast<UChunk>(ac);
	//uc->pos = pos;
	//uc->ReregisterComponent();
	//UE_LOG(LogTemp, Error, TEXT("Chunkactor loc %.1f %.1f %.1f"), pos.X, pos.Y, pos.Z);
	//uc->SetRelativeLocation(pos);
	//ac->RegisterComponent();
	vertices.Empty();
	triangles.Empty();
	UVs.Empty();
	cbg->noise.SetSeed(132);
	//cbg.noise.SetSeed(time(NULL));
	
	//cbg->generateBlocks(pos.X / triangleSize / 2, pos.Y / triangleSize / 2, pos.Z / triangleSize / 2, d3);

	//UE_LOG(LogTemp, Error, TEXT("Chunk loc %d"), d3[532].id);

	//ThreadWorker tw;
	//std::thread th(&ThreadWorker::threadFunction, cbg, pos, d3);
	//th.join();
	chunkWorker = new ChunkWorker(this, cbg, cmg);
	//chunkWorker->Thread->WaitForCompletion();
	//cbg->generateBlocks(pos.X / triangleSize / 2, pos.Y / triangleSize / 2, pos.Z / triangleSize / 2, d3);

	


	//delete[] &d3;
	//vertices.Empty();
	//triangles.Empty();
	//UVs.Empty();

}


// Called every frame
void AChunkActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

