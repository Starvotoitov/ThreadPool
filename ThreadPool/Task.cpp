#include "Task.h"

Task::Task(): TaskStatus(Waiting)
{
	InitializeCriticalSectionAndSpinCount(&WaitCS, DefaultSpinCount);
	InitializeConditionVariable(&WaitCV);
}

Task::Task(Function Func): Action(Func), TaskStatus(Waiting)
{
	InitializeCriticalSectionAndSpinCount(&WaitCS, DefaultSpinCount);
	InitializeConditionVariable(&WaitCV);
}

Task::~Task()
{
	DeleteCriticalSection(&WaitCS);
}

void Task::RunFunction()
{
	reinterpret_cast<Function>(ActionFunc)();
}

void Task::Execute()
{
	EnterCriticalSection(&WaitCS);
	TaskStatus = InProgress;
	RunFunction();
	TaskStatus = Done;
	WakeAllConditionVariable(&WaitCV);
	LeaveCriticalSection(&WaitCS);
}

void Task::Wait()
{
	EnterCriticalSection(&WaitCS);
	while (!IsDone())
	{
		SleepConditionVariableCS(&WaitCV, &WaitCS, INFINITE);
	}
	LeaveCriticalSection(&WaitCS);
}

Status Task::GetStatus()
{
	return TaskStatus;
}

bool Task::IsWaiting()
{
	return TaskStatus == Waiting;
}

bool Task::IsInProgress()
{
	return TaskStatus == InProgress;
}

bool Task::IsDone()
{
	return TaskStatus == Done;
}