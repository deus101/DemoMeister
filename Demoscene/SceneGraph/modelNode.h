#ifndef MODELNODE_HPP
#define MODELNODE_HPP

#include "assetNode.h"
//#include "shaders.h"
#include "../Engine/model.h"
#include "../Effect/GeomPacket.h"


namespace NS_SG{
	
		class modelNode : public assetNode
		{
		public:
			modelNode(std::string name,  NS_ENG::model  *mesh, NS_EFF::GeomPacket *tech) :
				assetNode(name),
				Model(mesh),
				Magic(tech),
				transparent(false)
			{}

			bool isTransparent()
			{
				return transparent;
			}

			void draw()
			{
				//M3DMatrix44f ABS;
				//getAbsoluteTransform(ABS);
				assert(NULL != Model);
				assert(NULL != Magic);
				//Magic->Draw(Model, ABS);
			}

			bool transparent;

			NS_ENG::model *Model;
			NS_EFF::GeomPacket *Magic;

		};

	



}

#endif