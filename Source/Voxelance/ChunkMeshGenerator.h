// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "ChunkActor.h"
#include "BlockLib.h"

class VOXELANCE_API ChunkMeshGenerator
{

public:
	ChunkMeshGenerator();

	static void generateMesh(FBlock* blocks3d, TArray<FVector>& vertices, TArray<int>& triangles, TArray<FVector2D>& uvs);
	static void init();

	static TArray<FVector> meshFaces[6];
	static TArray<int> meshTris[6];
};
