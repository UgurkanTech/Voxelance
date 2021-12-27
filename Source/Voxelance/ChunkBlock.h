#pragma once
#include "ChunkActor.h"
#include "Mutex.h"
#include "Misc/Crc.h"

enum EChunkState
{
	Pooled,
	Dirty,
	ReadyToRender,
	Rendered,
	ToBeDeleted,
	Deleted
	
};
struct FChunkBlock
{
	
	FChunkBlock(){}
	
	FChunkBlock(AChunkActor* actor)
	{
		this->Actor = actor;
		this->Pos = actor->pos;
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
	
	FVector Pos;
	AChunkActor* Actor = nullptr;
	Mutex mutex;

	EChunkState State = Pooled;
	
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
