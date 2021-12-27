// Fill out your copyright notice in the Description page of Project Settings.


#include "ChunkBlockGen.h"

ChunkBlockGen::ChunkBlockGen()
{
	simplex = new SimplexNoise(0.001f,1,1,1);
}

ChunkBlockGen::~ChunkBlockGen()
{
}

void ChunkBlockGen::generateBlocks(float x, float y, float z, FBlock* blocks) {
	int n;
	for (size_t i = 0; i < blockCount; i++)
	{

				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 15 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 14 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 13 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 12 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 11 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 10 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 9 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 8 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 7 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 6 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 5 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 6 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 8 + 4;
				n = (noise.GetNoise(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1)) + 1) * 15 + 4;

				//float n = USimplexNoiseBPLibrary::GetSimplexNoise2D_EX(x + (i & xyMaxSub1), y + ((i >> 4) & xyMaxSub1),1.2f, 0.9f, 2, 2.4f, true) * 5 + 4;
				
				if ((i >> 8) == 0) {
					blocks[i].id = 5;
					blocks[i].isOpaque = true;
				}
				else if (n == (i >> 8)) {
					blocks[i].id = 2;
					blocks[i].isOpaque = true;
				}

				else if (n - 4 > (i >> 8)) {
					blocks[i].id = 1;
					blocks[i].isOpaque = true;
				}
				else if (n > (i >> 8)) {
					blocks[i].id = 4;
					blocks[i].isOpaque = true;
				}
				else
				{
					blocks[i].id = 0;
					blocks[i].isOpaque = false;
				}

	}
}

