#ifndef _DECORATOR_H_
#define _DECORATOR_H_

#include <SelectorNode.h>
#include <functional>

namespace BT
{
	class Decorator : public SelectorNode
	{
	public:
		Decorator(std::string _id, unsigned tick_number = -1);
		virtual void reset() override;
		virtual NodeStatus tick() override;
		virtual void addChildNode(TreeNode* new_child_node) override;
	private:
		unsigned allowed_ticks;
		unsigned ticks;
	};
}

#endif