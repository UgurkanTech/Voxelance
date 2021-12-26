// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Block.generated.h"


USTRUCT(BlueprintType)
struct FBlock
{
    GENERATED_BODY()
public:
    FBlock() {};
    FBlock(uint8 id, uint8  meta, bool isOpaque) {
        this->id = id;
        this->meta = meta;
        this->isOpaque = isOpaque;

    };
        uint8  id;
        uint8  meta;
        bool isOpaque;
};

