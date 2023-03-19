#include "Thread.h"
#include "Logs.h"

unsigned long WINAPI Thread::ThreadFunction(LPVOID pv)
{
	try { (reinterpret_cast<Thread *>(pv))->Run(); }
	catch(...) { return 1; }
	return 0;
}

unsigned long Thread::GetCurrentThreadId()
{
	return ::GetCurrentThreadId();
}

void Thread::CurrentThreadSleep(unsigned long ms)
{
	::Sleep(ms);
}

Thread::Thread(void) {}
Thread::~Thread(void) {}

unsigned long Thread::Start()
{
	unsigned long id;
	if(::CreateThread(NULL, 0, ThreadFunction, this, 0, &id) == NULL) LLE()
	//TODO: SetPriorityClass , SetThreadPriority
	return id;
}