// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockLib.h"
FBlockLib::FBlockLib() {
	blocks.Add(FBlockMeta("Air", 0, 0, "-", 0, false));
	blocks.Add(FBlockMeta("Stone", 1, 0, "-", 0, true));
	blocks.Add(FBlockMeta("Grass", 2, 0, "-", 8, 2, 3, 3, 3, 3, true));
	blocks.Add(FBlockMeta("Glass", 3, 0, "-", 11, false));
}
