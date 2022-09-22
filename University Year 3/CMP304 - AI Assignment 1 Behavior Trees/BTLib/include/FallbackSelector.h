#ifndef _FALLBACK_SELECTOR_H_
#define _FALLBACK_SELECTOR_H_

#include <SelectorNode.h>
#include <functional>

namespace BT
{
	class FallbackSelector : public SelectorNode
	{
	public:
		FallbackSelector(std::string _id);
		virtual void reset() override;
		virtual NodeStatus tick() override;
	private:
		unsigned running_index = 0;
	};
}

#endif