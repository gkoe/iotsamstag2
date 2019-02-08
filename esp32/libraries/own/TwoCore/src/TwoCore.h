
#include <Arduino.h>
#include <list>

class TwoCore
{
public:

	void init();
	void Task(TaskFunction_t function);

private:
	//std::list<TaskHandle_t> _tasks;

};
