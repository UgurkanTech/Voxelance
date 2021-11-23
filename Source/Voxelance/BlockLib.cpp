// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLib.h"
FBlockLib::FBlockLib() {
	blocks.Add(FBlockMeta("Air", 0, 0, "-", 0, false));
	blocks.Add(FBlockMeta("Stone", 1, 0, "-", 12, true));
	blocks.Add(FBlockMeta("Grass", 2, 0, "-", 14, 13, 15, 15, 15, 15, true));
	blocks.Add(FBlockMeta("Glass", 3, 0, "-", 8, false));
	blocks.Add(FBlockMeta("Dirt", 4, 0, "-", 13, true));
	blocks.Add(FBlockMeta("Bedrock", 5, 0, "-", 7, true));
	blocks.Add(FBlockMeta("Gold", 6, 0, "-", 9, true));
	blocks.Add(FBlockMeta("Lapis", 7, 0, "-", 1, true));
}
