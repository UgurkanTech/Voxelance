// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkMeshGenerator.h"


void UChunkMeshGenerator::Execute(FBlock3D blocks3d, const int y, int& r1, int& r2)
{
    FBlock2D* blocks = blocks3d.blocks.GetData();
    uint32 elementSizeFirst = blocks3d.blocks.GetTypeSize();
    
}
