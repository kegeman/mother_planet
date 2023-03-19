#pragma once
#include "Win32.h"
class Thread
{
private:
	static unsigned long WINAPI ThreadFunction(LPVOID pv);
public:
	static unsigned long GetCurrentThreadId();
	static void CurrentThreadSleep(unsigned long ms=1);
public:
	Thread(void);
	virtual ~Thread(void);
	virtual void Run()=0; // Do the job!
	unsigned long Start();
private:
//	mutable HRESULT hr;
};

