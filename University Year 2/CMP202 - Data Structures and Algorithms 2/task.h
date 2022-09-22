#ifndef TASK_H
#define TASK_H
class task
{
public:
	virtual ~task()
	{
	}


	virtual void run() = 0;
};

#endif

