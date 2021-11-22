// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockMeta.generated.h"

USTRUCT(BlueprintType)
struct FBlockMeta
{
    GENERATED_BODY()
public:
    FBlockMeta() {
        this->name = "NULL";
        this->id = 0;
        this->meta = 0;
        this->desc = "NULL";
        this->uvIds.Add(0);
        this->uvIds.Add(0);
        this->uvIds.Add(0);
        this->uvIds.Add(0);
        this->uvIds.Add(0);
        this->uvIds.Add(0);
        this->isOpaque = false;

    }
    FBlockMeta(FString name, int id, int meta, FString desc, int uv_top_id, int uv_bottom_id, int uv_back_id, int uv_front_id, int uv_left_id, int uv_right_id, bool isOpaque)
    {
        this->name = name;
        this->id = id;
        this->meta = meta;
        this->desc = desc;
        this->uvIds.Add(uv_top_id);
        this->uvIds.Add(uv_bottom_id);
        this->uvIds.Add(uv_back_id);
        this->uvIds.Add(uv_front_id);
        this->uvIds.Add(uv_left_id);
        this->uvIds.Add(uv_right_id);
        this->isOpaque = isOpaque;
    }
    FBlockMeta(FString name, int id, int meta, FString desc, int uv_id, bool isOpaque)
    {
        this->name = name;
        this->id = id;
        this->meta = meta;
        this->desc = desc;
        this->uvIds.Add(uv_id);
        this->uvIds.Add(uv_id);
        this->uvIds.Add(uv_id);
        this->uvIds.Add(uv_id);
        this->uvIds.Add(uv_id);
        this->uvIds.Add(uv_id);
        this->isOpaque = isOpaque;
    }
    UPROPERTY(BlueprintReadWrite)
        FString name;
    UPROPERTY(BlueprintReadWrite)
        int id;
    UPROPERTY(BlueprintReadWrite)
        int meta;
    UPROPERTY(BlueprintReadWrite)
        FString desc;
    UPROPERTY(BlueprintReadWrite)
        TArray<int> uvIds;
    UPROPERTY(BlueprintReadWrite)
        bool isOpaque;
};