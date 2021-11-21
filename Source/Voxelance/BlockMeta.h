// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlockMeta.generated.h"

USTRUCT(BlueprintType)
struct FBlockMeta
{
    GENERATED_BODY()
public:
    FBlockMeta() {}
    FBlockMeta(FString name, int id, int meta, FString desc, int uv_top_id, int uv_bottom_id, int uv_back_id, int uv_front_id, int uv_left_id, int uv_right_id, bool isOpaque)
    {
        this->name = name;
        this->id = id;
        this->meta = meta;
        this->desc = desc;
        this->uv_top_id = uv_top_id;
        this->uv_bottom_id = uv_bottom_id;
        this->uv_back_id = uv_back_id;
        this->uv_front_id = uv_front_id;
        this->uv_left_id = uv_left_id;
        this->uv_right_id = uv_right_id;
        this->isOpaque = isOpaque;
    }
    FBlockMeta(FString name, int id, int meta, FString desc, int uv_id, bool isOpaque)
    {
        this->name = name;
        this->id = id;
        this->meta = meta;
        this->desc = desc;
        this->uv_top_id = uv_id;
        this->uv_bottom_id = uv_id;
        this->uv_back_id = uv_id;
        this->uv_front_id = uv_id;
        this->uv_left_id = uv_id;
        this->uv_right_id = uv_id;
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
        int uv_top_id;
    UPROPERTY(BlueprintReadWrite)
        int uv_bottom_id;
    UPROPERTY(BlueprintReadWrite)
        int uv_back_id;
    UPROPERTY(BlueprintReadWrite)
        int uv_front_id;
    UPROPERTY(BlueprintReadWrite)
        int uv_left_id;
    UPROPERTY(BlueprintReadWrite)
        int uv_right_id;
    UPROPERTY(BlueprintReadWrite)
        bool isOpaque;
};