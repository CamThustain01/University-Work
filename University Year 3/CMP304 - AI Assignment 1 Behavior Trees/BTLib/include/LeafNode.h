#ifndef _LEAF_NODE_H_
#define _LEAF_NODE_H_

#include <TreeNode.h>
#include <functional>

namespace BT 
{
	class Blackboard;

	class LeafNode : public TreeNode
	{
	public:
		LeafNode(std::string _id);
		LeafNode(std::string _id, std::function<NodeStatus(TreeNode*)> new_run_func);
		void setRunFunction(std::function<NodeStatus(TreeNode*)> new_run_func);
		void reset() override;
		NodeStatus tick() override;
	private:
		std::function<NodeStatus(TreeNode*)> run_func;
	};
}

#endif