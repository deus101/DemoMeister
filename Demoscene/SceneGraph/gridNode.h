#pragma once
//Should I make a "procedural" node?
#include "assetNode.h"
#include "../Engine/GridPoints.h"
#include "../Effect/GeomPacket.h"

namespace NS_SG{


	class gridNode : public assetNode{


	public:

		gridNode(std::string name, NS_ENG::GridPoints  *grid, NS_EFF::HeightMapPacket *tech) :
			assetNode(name),
			Grid(grid),
			Magic(tech),
			transparent(false)
		{}

		 bool isTransparent()
		{
			return transparent;
		}

		 void Draw()
		{

			assert(NULL != Grid);
			assert(NULL != Magic);

		}

		bool transparent;
		 NodeType getType() { return NODE_ASSET; }

		NS_EFF::HeightMapPacket *getMagic(){ return Magic; }
		//During get asset the asset classes could perform their various buffer updates.
		NS_ENG::GridPoints *getAsset(){ return Grid; }


		NS_ENG::GridPoints *Grid;
		NS_EFF::HeightMapPacket *Magic;
	};

}