#pragma once
#include "node.h"

namespace NS_SG{

	
		class assetNode : public node
		{
		public: 
			assetNode( std::string name) : node(name) { }
			NodeType getType() { return NODE_ASSET; }

			virtual bool isTransparent() = 0;
			virtual void Draw() = 0;
		};
	
}
