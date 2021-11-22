// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockMeta.h"
#include "BlockLib.generated.h"

USTRUCT(BlueprintType)
struct FBlockLib
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
         TArray<FBlockMeta> blocks;
    FBlockLib();
};
