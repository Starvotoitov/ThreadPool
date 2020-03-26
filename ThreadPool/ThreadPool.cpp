#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	InitializeThreadPool(DefaultThreadsCount);
}

ThreadPool::ThreadPool(int ThreadsCount)
{
	InitializeThreadPool(ThreadsCount);
}

ThreadPool::~ThreadPool()
{
	Abort();
	DeleteSynchronizationBarrier(&CloseBarrier);
	DeleteCriticalSection(&ActionQueueCS);
}

void ThreadPool::InitializeThreadPool(int ThreadsCount)
{
	InitializeCriticalSectionAndSpinCount(&ActionQueueCS, DefaultSpinCount);
	InitializeConditionVariable(&ActionQueueCV);
	InitializeSynchronizationBarrier(&CloseBarrier, ThreadsCount + 1, DefaultSpinCount);
	for (int i = 0; i < ThreadsCount; i++)
	{
		ThreadList.push_back(CreateThread(NULL, 0, ThreadRoutine, this, 0, NULL));
	}
}

void ThreadPool::AddAction(Action* AddedAction)
{
	if (AddedAction != NULL)
	{
		EnterCriticalSection(&ActionQueueCS);
		ActionQueue.push(AddedAction);
		WakeConditionVariable(&ActionQueueCV);
		LeaveCriticalSection(&ActionQueueCS);
	}
}

Action* ThreadPool::GetNextAction()
{
	Action* ExtractedAction = nullptr;
	EnterCriticalSection(&ActionQueueCS);
	while (ActionQueue.empty())
	{
		SleepConditionVariableCS(&ActionQueueCV, &ActionQueueCS, INFINITE);
	}
	ExtractedAction = ActionQueue.front();
	ActionQueue.pop();
	LeaveCriticalSection(&ActionQueueCS);
	return ExtractedAction;
}

DWORD WINAPI ThreadPool::ThreadRoutine(void* Param)
{
	ThreadPool* This = reinterpret_cast<ThreadPool*>(Param);
	try
	{
		while (true)
		{
			Action* NewAction = This->GetNextAction();
			NewAction->Execute();
		}
	}
	catch (ThreadAbortException)
	{
		EnterSynchronizationBarrier(&This->CloseBarrier, 0);
	}

	return 0;
}

void ThreadPool::Abort()
{
	for (HANDLE Thread : ThreadList)
	{
		TerminateThread(Thread, 0);
		CloseHandle(Thread);
	}
}

void ThreadPool::CloseThread()
{
	throw ThreadAbortException();
}

void ThreadPool::Close()
{
	list<Action*> CloseActions;
	for (int i = 0; i < ThreadList.size(); i++)
	{
		Action* CloseAct = new Action(CloseThread);
		CloseActions.push_back(CloseAct);
		AddAction(CloseAct);
	}

	EnterSynchronizationBarrier(&CloseBarrier, 0);

	for (Action* Act : CloseActions)
	{
		delete Act;
	}

	for (HANDLE Thread : ThreadList)
	{
		CloseHandle(Thread);
	}

	ThreadList.clear();
}

void ThreadPool::operator+=(Action* AddedAction)
{
	AddAction(AddedAction);
}

void ThreadPool::operator+=(Action& AddedAction)
{
	AddAction(&AddedAction);
}
