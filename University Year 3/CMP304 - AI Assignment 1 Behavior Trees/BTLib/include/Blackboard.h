#ifndef _BLACKBOARD_H_
#define _BLACKBOARD_H_

#include <map>
#include <string>

namespace BT
{
	class Blackboard
	{
	public:
		static Blackboard* getInstance();
		void addNewValue(std::string name, int data);
		int getValue(std::string name);
		int getAndDeleteValue(std::string name);
		void editValue(std::string name, int new_value);
	private:
		std::map<std::string, int> datamap;
	};
}

#endif