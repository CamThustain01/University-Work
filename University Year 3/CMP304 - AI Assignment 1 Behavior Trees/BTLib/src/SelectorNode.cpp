#include "SelectorNode.h"

namespace BT
{
	SelectorNode::SelectorNode(std::string id_)
		: TreeNode(id_)
	{
	}

	void SelectorNode::reset()
	{
		for (auto node : child_nodes)
		{
			node->reset();
		}
	}

	void SelectorNode::addChildNode(TreeNode* new_child_node)
	{
		child_nodes.push_back(new_child_node);
	}

	TreeNode* SelectorNode::getChildNode(unsigned index)
	{
		if (index >= child_nodes.size())
			return nullptr;

		return child_nodes[index];
	}

	TreeNode* SelectorNode::getChildNodeByID(std::string id)
	{
		for (auto node : child_nodes)
		{
			if (node->getID() == id)
				return node;
		}

		return nullptr;
	}

	void SelectorNode::removeChild(unsigned index)
	{
		if (index <= child_nodes.size())
		{
			child_nodes.erase(child_nodes.begin() + index);
		}
	}

	void SelectorNode::removeChildByID(std::string id)
	{
		auto iterator = child_nodes.begin();

		for (iterator; iterator != child_nodes.end(); iterator++)
		{
			if ((*iterator)->getID() == id)
			{
				break;
			}
		}

		if (iterator != child_nodes.end())
		{
			child_nodes.erase(iterator);
		}
	}
}