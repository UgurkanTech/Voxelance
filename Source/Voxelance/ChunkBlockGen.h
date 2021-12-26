// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <FastNoiseGenerator\Public\FastNoiseWrapper.h>
#include "FastNoiseLite.h"
#include "SimplexNoise.h"
#include "SimplexNoiseBPLibrary.h"
#include "Block.h"
#include "ChunkActor.h"
#include "BlockLib.h"

class VOXELANCE_API ChunkBlockGen
{
public:
	FastNoiseLite noise;
	SimplexNoise* simplex;
	
	ChunkBlockGen();
	~ChunkBlockGen();
	void generateBlocks(float x, float y, float z, FBlock* blocks);
	
};
