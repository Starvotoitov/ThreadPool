#ifndef PARAMETERIZE_TASK_WITH_RESULT 
#define PARAMETERIZE_TASK_WITH_RESULT

#include "ParameterizeTask.h"

template<typename InputType, typename OutputType>
class ParameterizeTaskWithResult: public ParameterizeTask<InputType>
{
public:
	typedef OutputType(*Function)(InputType);

	ParameterizeTaskWithResult();
	ParameterizeTaskWithResult(Function Func, InputType Parameter);
	OutputType GetResult();
protected:
	virtual void RunFunction();
private:
	OutputType Result;
};

template<typename InputType, typename OutputType>
ParameterizeTaskWithResult<InputType, OutputType>::ParameterizeTaskWithResult()
{
}

template<typename InputType, typename OutputType>
ParameterizeTaskWithResult<InputType, OutputType>::ParameterizeTaskWithResult(Function Func, InputType Parameter)
{
	ParameterizeTask<InputType>::ActionFunc = Func;
	ParameterizeTask<InputType>::TaskParameter = Parameter;
}

template<typename InputType, typename OutputType>
OutputType ParameterizeTaskWithResult<InputType, OutputType>::GetResult()
{
	return Result;
}

template<typename InputType, typename OutputType>
void ParameterizeTaskWithResult<InputType, OutputType>::RunFunction()
{
	Result = reinterpret_cast<Function>(ParameterizeTask<InputType>::ActionFunc)(ParameterizeTask<InputType>::TaskParameter);
}

#endif

