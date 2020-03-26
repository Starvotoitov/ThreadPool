#ifndef TASK
#define TASK

#include "Action.h"
#include "Status.h"
#include "NoFunctionException.h"
#include <Windows.h>

using namespace std;

class Task : public Action
{
public:
	typedef void (*Function)(void);

	Task();
	Task(Function Func);
	virtual ~Task();
	virtual void Execute();
	void Wait();
	Status GetStatus();
	bool IsWaiting();
	bool IsInProgress();
	bool IsDone();

protected:
	void virtual RunFunction();
private:
	static const int DefaultSpinCount = 2000;
	CRITICAL_SECTION WaitCS;
	CONDITION_VARIABLE WaitCV;
	Status TaskStatus;
};

#endif