#ifndef TASK_WITH_RESULT
#define TASK_WITH_RESULT

#include "Task.h"

template<typename OutputType>
class TaskWithResult: public Task
{
public:
	typedef OutputType(*Function)(void);

	TaskWithResult();
	TaskWithResult(Function Func);
	OutputType GetResult();
protected:
	virtual void RunFunction();
private:
	OutputType Result;
};

template<typename OutputType>
TaskWithResult<OutputType>::TaskWithResult()
{
}

template<typename OutputType>
TaskWithResult<OutputType>::TaskWithResult(Function Func)
{
	ActionFunc = Func;
}

template<typename OutputType>
OutputType TaskWithResult<OutputType>::GetResult()
{
	return Result;
}

template<typename OutputType>
void TaskWithResult<OutputType>::RunFunction()
{
	Result = reinterpret_cast<Function>(ActionFunc)();
}

#endif
