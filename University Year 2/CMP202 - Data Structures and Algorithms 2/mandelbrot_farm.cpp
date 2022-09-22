#include "mandelbrot_farm.h"
#include<thread>
#include <vector>


using std::thread;
using std::vector;

void mandelbrot_farm::add_task(task* task_)
{

	//add a pointer of task to the task queue
	task_queue.push(task_);
}

void mandelbrot_farm::run()
{
	core_num = std::thread::hardware_concurrency();//core num eqaul to hardware concurrency thread (my laptop has 12)
	
	//variable for testing different values...
	//int core_num_2 = 4;

	std::vector<thread*> thread_vector;//create a vector thread called thread_vector


	for (int i = 0; i < core_num; i++) { //run for however many cores our hardware has 


		std::thread* worker = new std::thread([this]() //creates a thread called worker
			{
				while (!empty_()) //while its empty
				{
					task* task_; // create a pointer to task 
					task_ = pop_and_take(); // pop and take the task 
					task_->run(); //run the task
					
					delete task_; //delete task
				}
			});


		thread_vector.push_back(worker); //push back our worker

	}

	for (int i = 0; i < core_num; i++)
	{
		thread_vector[i]->join();//join the thread vector for however many cores our hardware has
	}
}

bool mandelbrot_farm::empty_()
{
	queue_mutex_.lock(); //lock our queue mutex
	bool i = task_queue.empty(); //create a bool i annd make it equal to the empty queue
	queue_mutex_.unlock(); //unlock the mutex 
	return i; //return boolean i 
}

task* mandelbrot_farm::front_()
{
	queue_mutex_.lock(); //lock mutex again 
	task* f = task_queue.front(); //create a pointer to task called f (for front) make it equal to the front of the queue
	queue_mutex_.unlock(); //unlock mutex
	return f; //return f
}

void mandelbrot_farm::push_(task* task_)
{
	queue_mutex_.lock(); //lock mutex
	task_queue.push(task_); //push our task onto the queue
	queue_mutex_.unlock(); //unlock mutex
}

void mandelbrot_farm::pop_()
{
	queue_mutex_.lock(); //lock our mutex
	task_queue.pop(); //pop whatevers on top of the queue
	queue_mutex_.unlock();//unlock mutex
}

task* mandelbrot_farm::pop_and_take()
{
	queue_mutex_.lock();//lock mutex
	task* q = task_queue.front(); //create a pointer of task called q make it equal to the front of the queue
	task_queue.pop(); //pop whatever is on top of the queue
	queue_mutex_.unlock();//unlock the mutex
	return q; //return q
}