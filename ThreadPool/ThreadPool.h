#ifndef THREAD_POOL
#define THREAD_POOL

#include <queue>
#include <list>
#include <Windows.h>
#include "Action.h"

using namespace std;

class ThreadPool
{
public:
	ThreadPool();
	ThreadPool(int ThreadsCount);
	virtual ~ThreadPool(); //
	void AddAction(Action* AddedAction);
	void WaitAll();
	void Abort();
	void Close();
	void operator+=(Action* AddedAction);
	void operator+=(Action& AddedAction);

private:
	class ThreadAbortException
	{};

	static const int DefaultThreadsCount = 100;
	static const int DefaultSpinCount = 2000;
	static const int MaxThreadCount = 500; //
	static const int MinThreadCount = 5; //

	CRITICAL_SECTION ActionQueueCS;
	CONDITION_VARIABLE ActionQueueCV;
	SYNCHRONIZATION_BARRIER CloseBarrier;
	queue<Action*> ActionQueue;
	list<HANDLE> ThreadList;
	
	void InitializeThreadPool(int ThreadsCount);
	Action* GetNextAction();

	static DWORD WINAPI ThreadRoutine(void* Param);
	static void CloseThread();
};

#endif