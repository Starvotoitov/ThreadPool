#include "Action.h"

Action::Action() : ActionFunc(NoFunction)
{}

Action::Action(Function Func): ActionFunc(Func)
{
}

Action::~Action()
{
}

void Action::Execute()
{
	RunFunction();
}

void Action::RunFunction()
{
	reinterpret_cast<Function>(ActionFunc)();
}

void Action::NoFunction()
{
	throw NoFunctionException();
}