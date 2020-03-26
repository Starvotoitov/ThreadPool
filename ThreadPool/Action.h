#ifndef ACTION
#define ACTION

#include "NoFunctionException.h"

class Action
{
public:
	typedef void (*Function)(void);

	Action();
	Action(Function Func);
	virtual ~Action();
	virtual void Execute();

protected:
	void* ActionFunc;
	virtual void RunFunction();
private:
	static void NoFunction();
};

#endif