// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class VOXELANCE_API Mutex
{
public:
	//the default constructor
	Mutex()
	{
		Windows::InitializeCriticalSection(&m_criticalSection);
	}

	//destructor
	~Mutex()
	{
		Windows::DeleteCriticalSection(&m_criticalSection);
	}

	//lock
	void Lock()
	{
		Windows::EnterCriticalSection(&m_criticalSection);
	}

	//unlock
	void Unlock()
	{
		Windows::LeaveCriticalSection(&m_criticalSection);
	}
	Windows::BOOL tryLock()
	{
		return Windows::TryEnterCriticalSection(&m_criticalSection);
	}

private:
	Windows::CRITICAL_SECTION m_criticalSection;
};