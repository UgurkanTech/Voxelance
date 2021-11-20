// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.generated.h"

USTRUCT(BlueprintType)
struct FBlock
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        int id;
    UPROPERTY(BlueprintReadWrite)
        int meta;
};

USTRUCT(BlueprintType)
struct FBlock1D
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        TArray<FBlock> blocks;
};

USTRUCT(BlueprintType)
struct FBlock2D
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        TArray<FBlock1D> blocks;
};

USTRUCT(BlueprintType)
struct FBlock3D
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite)
        TArray<FBlock2D> blocks;
};