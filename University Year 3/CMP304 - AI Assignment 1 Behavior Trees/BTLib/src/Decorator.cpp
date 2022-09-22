#include "Decorator.h"

namespace BT
{
	Decorator::Decorator(std::string _id, unsigned tick_number)
		: SelectorNode(_id)
		, allowed_ticks(tick_number)
		, ticks(0)
	{
	}

	void Decorator::reset()
	{
		SelectorNode::reset();
		ticks = 0;
		setStatus(NodeStatus::NODE_IDLE);
	}

	NodeStatus Decorator::tick()
	{
		// If not running, start running
		if (getStatus() == NodeStatus::NODE_IDLE)
		{
			init();
		}
		else if (getStatus() == NodeStatus::NODE_RUNNING)
		{
			if (ticks <= allowed_ticks)
			{
				NodeStatus result = getChildNode(0)->tick();
				ticks++;
				if (result == NodeStatus::NODE_SUCCESS || result == NodeStatus::NODE_FAILURE)
				{
					setStatus(result);
				}
			}
			else
			{
				setStatus(NodeStatus::NODE_SUCCESS);
			}
		}

		return getStatus();
	}

	void Decorator::addChildNode(TreeNode* new_child_node)
	{
		if (getNumberOfChildNodes() == 0) {
			SelectorNode::addChildNode(new_child_node);
		}
	}
}