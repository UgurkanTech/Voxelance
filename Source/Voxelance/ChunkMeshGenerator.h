// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Block.h"
#include "BlockLib.h"

#include "ChunkMeshGenerator.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMiniTimerOutputPin);
UCLASS()
class VOXELANCE_API UChunkMeshGenerator : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	UChunkMeshGenerator();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate Chunk Mesh", Keywords = "Chunk Mesh Generator"))
		static void Execute(FBlock3D blocks3d, const int triSize, const FVector2D tileSize, FBlockLib blockLib, TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector2D>& uvs);
	static void CalculateTrisVerts(FVector pos, const int triSize, TArray<FVector>& verts, TArray<int>& tris, TArray<FVector> faceMeshVerts, TArray<int> faceMeshTris);

	static TArray<FVector> meshFaces[6];
	static TArray<int> meshTris[6];
};
