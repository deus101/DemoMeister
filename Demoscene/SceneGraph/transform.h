#pragma once
#include "node.h"
#include "math3d.h"
namespace sg
{
	namespace noder
	{
		class transform : public node
		{
		public:
			transform(std::string name) : node(name) {}
			virtual NodeType getType() { return NODE_TRANSFORM; }
		};
	}
}