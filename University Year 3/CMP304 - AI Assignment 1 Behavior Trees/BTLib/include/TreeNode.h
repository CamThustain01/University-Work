#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#include <NodeStatus.h>
#include <string>

namespace BT
{
	class TreeNode
	{
	public:
		TreeNode(std::string id_) :
			status(NodeStatus::NODE_IDLE),
			id(id_)
		{}
		virtual void init() {
			reset();
			setStatus(NodeStatus::NODE_RUNNING);
		}
		virtual void reset() = 0;
		virtual NodeStatus tick() = 0;
		NodeStatus getStatus() { return status; }
		std::string getID() { return id; }
	protected:
		void setStatus(NodeStatus new_status) { status = new_status; }
	private:
		NodeStatus status;
		std::string id;
	};
}

#endif