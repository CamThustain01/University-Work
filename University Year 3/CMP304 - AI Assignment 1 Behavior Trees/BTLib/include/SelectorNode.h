#ifndef _SELECTOR_NODE_H_
#define _SELECTOR_NODE_H_

#include <TreeNode.h>
#include <vector>

namespace BT
{
	class SelectorNode : public TreeNode
	{
	public:
		SelectorNode(std::string _id);
		virtual void reset();
		virtual NodeStatus tick() { return getStatus(); }
		virtual void addChildNode(TreeNode* new_child_node);
		TreeNode* getChildNode(unsigned index);
		TreeNode* getChildNodeByID(std::string id);
		void removeChild(unsigned index);
		void removeChildByID(std::string id);
		size_t getNumberOfChildNodes() { return child_nodes.size(); }
	private:
		std::vector<TreeNode*> child_nodes;
	};
}

#endif