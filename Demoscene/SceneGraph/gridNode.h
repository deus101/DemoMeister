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

		virtual bool isTransparent()
		{
			return transparent;
		}

		virtual void Draw()
		{

			assert(NULL != Grid);
			assert(NULL != Magic);

		}

		bool transparent;
		virtual NodeType getType() { return NODE_ASSET; }


		NS_ENG::GridPoints *Grid;
		NS_EFF::HeightMapPacket *Magic;
	};

}