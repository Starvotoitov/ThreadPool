#ifndef PARAMETERIZE_ACTION
#define PARAMETERIZE_ACTION

#include "Action.h"
#include "NoFunctionException.h"

template<typename InputType>
class ParameterizeAction : public Action
{
public:
	typedef void (*Function)(InputType);

	ParameterizeAction();
	ParameterizeAction(Function Func, InputType Parameter);
protected:
	virtual void RunFunction();
private:
	InputType ActionParameter;
};

template<typename InputType>
ParameterizeAction<InputType>::ParameterizeAction()
{
}

template<typename InputType>
ParameterizeAction<InputType>::ParameterizeAction(Function Func, InputType Parameter) : ActionParameter(Parameter)
{
	ActionFunc = Func;
}

template<typename InputType>
void ParameterizeAction<InputType>::RunFunction()
{
	reinterpret_cast<Function>(ActionFunc)(ActionParameter);
}

#endif