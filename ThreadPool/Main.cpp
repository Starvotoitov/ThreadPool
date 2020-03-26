#include "ThreadPool.h"
#include "Action.h"
#include "ParameterizeAction.h"
#include "Task.h"
#include "TaskWithResult.h"
#include "ParameterizeTask.h"
#include "ParameterizeTaskWithResult.h"
#include <iostream>

using namespace std;

int Factorial(int Num)
{
	int Result = 1;
	for (int i = 1; i <= Num; i++)
	{
		Result *= i;
	}
	return Result;
}

int main()
{
	ThreadPool Pool(10);

	auto Task = new ParameterizeTaskWithResult<int, int>(Factorial, 10);

	Pool += Task;

	Task->Wait();

	cout << Task->GetResult() << endl;

	delete Task;
	Pool.Close();
	return 0;
}