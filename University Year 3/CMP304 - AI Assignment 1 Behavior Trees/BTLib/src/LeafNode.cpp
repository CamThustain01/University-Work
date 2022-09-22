#include "LeafNode.h"
#include <Blackboard.h>

namespace BT
{
	LeafNode::LeafNode(std::string _id)
		: TreeNode(_id)
	{
	}

	LeafNode::LeafNode(std::string _id, std::function<NodeStatus(TreeNode*)> new_run_func)
		: TreeNode(_id)
		, run_func(new_run_func)
	{
	}

	void LeafNode::setRunFunction(std::function<NodeStatus(TreeNode*)> new_run_func)
	{
		if (new_run_func)
		{
			run_func = new_run_func;
		}
	}

	void LeafNode::reset()
	{
		setStatus(NodeStatus::NODE_IDLE);
	}

	NodeStatus LeafNode::tick()
	{
		if (getStatus() == NodeStatus::NODE_IDLE)
		{
			init();
		}

		if (run_func && getStatus() == NodeStatus::NODE_RUNNING) {
			NodeStatus result = run_func(this);
			setStatus(result);
		}

		return getStatus();
	}
}