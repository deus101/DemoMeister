#ifndef MODELNODE_HPP
#define MODELNODE_HPP

#include "assetNode.h"
//#include "shaders.h"
#include "../Engine/model.h"

#include <DemoMeister\ShaderFu\DeferredPackets\GeomPacket.h>
//#include "../ShaderFu/DeferredPackets/GeomPacket.h"


namespace NS_SG{
	
		class modelNode : public assetNode
		{
		public:												//should I seperate between asset and procedural?
			modelNode(std::string name,  NS_ENG::model  *mesh, NS_EFF::GeomPacket *tech) :
				assetNode(name),
				Model(mesh),
				Magic(tech),
				transparent(false)
			{}

			~modelNode(){ }

			 bool isTransparent()
			{
				return transparent;
			}

			 void Draw()
			{
				//M3DMatrix44f ABS;
				//getAbsoluteTransform(ABS);
				assert(NULL != Model);
				assert(NULL != Magic);
				//Magic->Draw(Model, ABS);
				
			}

			bool transparent;
			NodeType getType() { return NODE_ASSET ; }
			NS_EFF::GeomPacket *getMagic(){ return Magic; }
			NS_ENG::model *getAsset(){ return Model; }


			NS_ENG::model *Model;
			NS_EFF::GeomPacket *Magic;

		};

	



}

#endif