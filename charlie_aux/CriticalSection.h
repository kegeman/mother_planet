#pragma once
#include "Win32.h"
class CriticalSection
{
public:
	CRITICAL_SECTION cs;

	CriticalSection(void)
	{
		::InitializeCriticalSection(&cs);
	}

	~CriticalSection(void)
	{
		::DeleteCriticalSection(&cs);
	}

	void Enter()
	{
		::EnterCriticalSection(&cs);
	}

	void Leave()
	{
		::LeaveCriticalSection(&cs);
	}
};

