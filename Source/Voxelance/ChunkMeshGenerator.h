// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Block.h"

#include "ChunkMeshGenerator.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMiniTimerOutputPin);
UCLASS()
class VOXELANCE_API UChunkMeshGenerator : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Generate Chunk Mesh", Keywords = "Chunk Mesh Generator"))
		static void Execute(FBlock3D blocks3d, int y, int& r1, int& r2);

};
