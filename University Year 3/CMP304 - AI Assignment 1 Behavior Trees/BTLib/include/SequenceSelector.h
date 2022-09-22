#ifndef _SEQUENCE_SELECTOR_H_
#define _SEQUENCE_SELECTOR_H_

#include <SelectorNode.h>
#include <functional>

namespace BT
{
	class SequenceSelector : public SelectorNode
	{
	public:
		SequenceSelector(std::string _id);
		virtual void reset() override;
		virtual NodeStatus tick() override;
	private:
		unsigned running_index = 0;
	};

	typedef SequenceSelector PriotitySelector;
}

#endif