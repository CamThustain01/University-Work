#include "Blackboard.h"

namespace BT
{
	Blackboard singleton;

	Blackboard* Blackboard::getInstance()
	{
		return &singleton;
	}

	void Blackboard::addNewValue(std::string name, int data)
	{
		datamap[name] = data;
	}

	int Blackboard::getValue(std::string name)
	{
		return datamap[name];
	}

	int Blackboard::getAndDeleteValue(std::string name)
	{
		int returnValue = datamap[name];
		datamap.erase(name);
		return returnValue;
	}

	void Blackboard::editValue(std::string name, int new_value)
	{
		datamap.erase(name);
		datamap[name] = new_value;
	}
}