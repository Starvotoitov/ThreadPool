#ifndef PARAMETERIZE_TASK
#define PARAMETERIZE_TASK

#include "Task.h"

template<typename InputType>
class ParameterizeTask : public Task
{
public:
	typedef void (*Function)(InputType);

	ParameterizeTask();
	ParameterizeTask(Function Func, InputType Parameter);
protected:
	virtual void RunFunction();
	InputType TaskParameter;
};

template<typename InputType>
ParameterizeTask<InputType>::ParameterizeTask()
{
}

template<typename InputType>
ParameterizeTask<InputType>::ParameterizeTask(Function Func, InputType Parameter): TaskParameter(Parameter)
{
	ActionFunc = Func;
}

template<typename InputType>
void ParameterizeTask<InputType>::RunFunction()
{
	reinterpret_cast<Function>(ActionFunc)(TaskParameter);
}

#endif