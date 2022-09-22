#pragma once
#include <queue>
#include <mutex>
#include "task.h"


using std::mutex;
using std::queue;


class mandelbrot_farm
{
public:

	void add_task(task* task_); //add_task function which takes task pointer as a parameter

	void run();//run function


private:
	std::queue<task*> task_queue;//queue
	std::mutex queue_mutex_;//mutex
	bool empty_(); //bool function called empty
	task* front_(); //task function called front
	void push_(task* task_); //push function which takes a task
	void pop_(); //pop function
	task* pop_and_take(); //task function called pop and take
	 
	int core_num; //variable called core num
};

