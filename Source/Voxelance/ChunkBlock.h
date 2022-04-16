#pragma once
#include "ChunkActor.h"
#include "Mutex.h"
#include "Misc/Crc.h"
#include "ChunkBlock.generated.h"

class AChunkActor;
UENUM()
enum EChunkState
{
	Pooled,
	Dirty,
	ReadyToRender,
	Rendered,
	ToBeDeleted,
	Deleted
	
};
USTRUCT()
struct FChunkBlock
{
	GENERATED_BODY()
	FChunkBlock(){}
	
	FChunkBlock(AChunkActor* actor)
	{
		this->Actor = actor;
	}
	FChunkBlock(FVector* pos)
	{
		this->Pos = *pos;
	}
	~FChunkBlock()
	{

		delete &Pos;
		delete &mutex;
		delete &State;
		delete this;
	}
	UPROPERTY()
	FVector Pos;
	
	//TSharedPtr<AChunkActor> Actor;
	AChunkActor* Actor;
	Mutex mutex;
	UPROPERTY()
	TEnumAsByte<EChunkState> State = Pooled;
	
	bool operator==(const FChunkBlock& Other) const
	{
		return Equals(Other);
	}

	bool Equals(const FChunkBlock& Other) const
	{
		return Pos.Equals(Other.Pos);
	}
#if UE_BUILD_DEBUG
	uint32 GetTypeHash(const FChunkBlock& Thing)
	{
		uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FChunkBlock));
		return Hash;
	}
#endif
};
