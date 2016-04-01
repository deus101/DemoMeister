#pragma once
#include "node.h"

namespace NS_SG{

	
		class assetNode : public node
		{
		public: 
			assetNode( std::string name) : node(name) { }
			~assetNode(){}
			NodeType getType() { return NODE_ASSET; }

			virtual bool isTransparent() = 0;
			virtual void Draw() = 0;

			virtual NS_EFF::renderPacket *getMagic() = 0;
			virtual NS_ENG::asset *getAsset() = 0;
		};
	
}
