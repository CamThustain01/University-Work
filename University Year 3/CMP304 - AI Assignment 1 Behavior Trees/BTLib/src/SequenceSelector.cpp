#include "SequenceSelector.h"

namespace BT
{
	SequenceSelector::SequenceSelector(std::string _id)
		: SelectorNode(_id)
	{
	}

	void SequenceSelector::reset()
	{
		SelectorNode::reset();
		running_index = 0;
		setStatus(NodeStatus::NODE_IDLE);
	}

	NodeStatus SequenceSelector::tick()
	{
		// If not running, start running
		if (getStatus() == NodeStatus::NODE_IDLE)
		{
			init();
		}
		else if (getStatus() == NodeStatus::NODE_RUNNING)
		{
			// If running, check if order of child classes. If running, then tick it, if not move on
			if (TreeNode* node = this->getChildNode(running_index))
			{
				NodeStatus result = node->tick();

				if (result == NodeStatus::NODE_SUCCESS) {
					running_index++;
					if (running_index >= getNumberOfChildNodes())
						setStatus(NodeStatus::NODE_SUCCESS);
				}
				else if (result == NodeStatus::NODE_FAILURE) {
					setStatus(NodeStatus::NODE_FAILURE);
				}
			}
		}

		return getStatus();
	}
}